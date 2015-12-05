#ICSVFit

Code needed to run SVFit on the grid - only works for Run 2 SVFit

As the total size of the input files is too large we can't send the svfit input files in the crab sandbox, so before using this the files need to be copied over to dcache (file_prefix specified in ICSVFit/SVFitTest/bin/SVFitTest.cpp)

Instructions:
ICSVFit relies on ICHiggsTauTau existing in $CMSSW_BASE/src/UserCode/ICHiggsTauTau. If you have that setup already:
```
cd $CMSSW_BASE/src/
git clone git@github.com:adewit/ICSVFit.git ICSVFit
scramv1 b
```

Move the SVFit input file directory over to ICSVFit/SVFitTest/<dcache-folder>, then copy the input files over to dcache <LINK TO SCRIPT>. Note that for this code to work the input files on dcache need to all be in the same directory. The dcache file path is specified in ICSVFit/SVFitTest/bin/SVFitTest.cpp as file_prefix.

To submit the jobs (after sourcing the crab environment):
```
cd ICSVFit/SVFitTest
./crabsub.py -i <dcache-folder> --name <request name> --area <crab area name>
```

Can then check on the status of jobs with the standard crab commands, once the jobs are done copy the output files back over to the analysis area and untar <LINK TO SCRIPT/INSTRUCTIONS>

