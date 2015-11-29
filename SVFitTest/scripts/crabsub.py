#!/usr/bin/env python
import os
import fnmatch
from optparse import OptionParser
print "AAAAAAAAAAAAAAA"

DRY_RUN = False
CRAB_PREFIX="""
set -x
set -e
ulimit -s unlimited
ulimit -c 0

function error_exit
{
  if [$1 -ne 0]; then
    echo "Error with exit code ${1}"
    if [ -e FrameworkJobReport.xml ]
    then
      cat << EOF > FrameworkJobReport.xml.tmp
      <FrameworkJobReport>
      <FrameworkError ExitStatus="${1}" Type="" >
      <Error with exit code ${1}
      </FrameworkError>
 EOF
     tail -n+2 FrameworkJobReport.xml >> FrameworkJobReport.xml.tmp
     mv FrameworkJobReport.xml.tmp FrameworkJobReport.xml
   else
     cat << EOF > FrameworkJobReport.xml
     <FrameworkJobReport>
     <FrameworkError ExitStatus="${1}" Type="" >
     Error with exit code ${1}
     </FrameworkError>
     </FrameworkJobReport>
EOF
     fi
     exit0
   fi
 }

trap 'error_exit $?' ERR
"""
CRAB_POSTFIX="""
tar -cf svfit_output.tar svfit_*_output.root
rm svfit_*_output.root
"""
task_name = "gridsvfittest3"
crab_area = "Nov292"
print "aaaa"
parser = OptionParser()
parser.add_option("-i", dest= "input",
                    help="sdfasdf")

(options, args) = parser.parse_args()

from CRABAPI.RawCommand import crabCommand
from httplib import HTTPException
print '>> crab3 requestName will be %s' %task_name
outscriptname = 'crab_%s.sh' %task_name
print '>> crab3 script will be %s' %outscriptname
outscript = open(outscriptname, "w")
outscript.write(CRAB_PREFIX)
jobs=0
wsp_files=set()

for root, dirnames, filenames in os.walk(options.input):
  for filename in fnmatch.filter(filenames, '*svfit_*_input.root'):
    print "next job"
    jobs += 1
    fullfile = os.path.join(root, filename)
    wsp_files.add(fullfile)
    outfile = fullfile.replace('input.root','output.root')
    outscript.write("./SVFitTest " + os.path.basename(fullfile) + '\n')

outscript.write(CRAB_POSTFIX)
outscript.close()

from ICHTT.ICSVFit.crab import config
config.General.requestName = task_name
config.JobType.scriptExe = outscriptname
config.JobType.inputFiles.extend(wsp_files)
config.Data.totalUnits = jobs
config.Data.outputDatasetTag= config.General.requestName
if crab_area is not None:
  config.General.workArea = crab_area
if not DRY_RUN:
  try:
    crabCommand('submit', config=config)
  except HTTPException, hte:
    print hte.headers
