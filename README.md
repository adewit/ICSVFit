#ICSVFit

Code needed to run SVFit on the grid - only works for Run 2 SVFit

As the total size of the input files is too large we can't send the svfit input files in the crab sandbox, so before using this the files need to be copied over to dcache. The directory you place the SVFit input files in on dcache will be referred to as path/to/input/folder/on/dcache.

Instructions:
ICSVFit relies on ICHiggsTauTau existing in $CMSSW_BASE/src/UserCode/ICHiggsTauTau. If you have that setup already:
```
cd $CMSSW_BASE/src/
git clone git@github.com:adewit/ICSVFit.git ICSVFit
scramv1 b
```

Move the SVFit input file directory over to ICSVFit/SVFitTest/<local-folder>, then copy the input files over to dcache (e.g. https://github.com/adewit/Scripts/blob/master/copy_svfit_input_files_to_dcache.py or something better). Note that for this code to work the input files on dcache need to all be in the same directory. The files in ICSVFit/SVFitTest/<local-folder> need to be the same as those in path/to/input/folder/on/dcache

To submit the jobs (after sourcing the crab environment):
```
cd ICSVFit/SVFitTest
./scripts/crabsub.py -i <local-folder> --name <request name> --area <crab area name> --file_prefix /path/to/input/folder/on/dcache
```

Can then check on the status of jobs with the standard crab commands, once the jobs are done copy the output files back over to the analysis area and untar (crab getoutput should work, then recursive untar) 

In addition to submitting crab jobs, we can also submit them to the batch, for example if we only need to run a very small number of jobs. For example:
```
cd ICSVFit/SVFitTest
./scripts/batch_sub.py -i <local-folder> --submit --jobsub="./scripts/submit_ic_batch_job.sh hepshort.q"
```
Generates jobs for the input files in <local-folder> and submits them to the IC short queue. The output files are written into <local-folder>

