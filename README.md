Hadoop on Cores


## Running

30 MB

./server 30000000 7000000 &

./client 30000000 7000000

## Experiment 1
exp1 file will contain
`./server 30000000 7000000 &`
`./client 30000000 7000000`


`./bin/hadoop jar ./share/hadoop/yarn/hadoop-yarn-applications-distributedshell-2.2.0.jar org.apache.hadoop.yarn.applications.distributedshell.Client --jar ./share/hadoop/yarn/hadoop-yarn-applications-distributedshell-2.2.0.jar --shell_command  <exp1> --num_containers 1`

## Sources
http://www.cs.cf.ac.uk/Dave/C/node27.html

