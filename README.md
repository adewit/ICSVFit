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

Move the SVFit input file directory over to ICSVFit/SVFitTest/<dcache-folder>, then copy the input files over to dcache (e.g. https://github.com/adewit/Scripts/blob/master/copy_svfit_input_files_to_dcache.py or something better). Note that for this code to work the input files on dcache need to all be in the same directory. The dcache file path is specified in ICSVFit/SVFitTest/bin/SVFitTest.cpp as file_prefix.

To submit the jobs (after sourcing the crab environment):
```
cd ICSVFit/SVFitTest
./crabsub.py -i <dcache-folder> --name <request name> --area <crab area name> --file_prefix <dcache_file_path>
```

Can then check on the status of jobs with the standard crab commands, once the jobs are done copy the output files back over to the analysis area and untar (crab -getouput should work, then recursive untar) 

In addition to submitting crab jobs, we can also submit them to the batch, for example if we only need to run a very small number of jobs. For example:
```
cd ICSVFit/SVFitTest
./scripts/batch_sub.py -i <dcache-folder> --submit --jobsub="./scripts/submit_ic_batch_job.sh hepshort.q"
```
Generates jobs for the input files in <dcache-folder> and submits them to the IC short queue. The output files are written into <dcache-folder>

