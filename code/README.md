# [Project name]

## Build instructions
From the `code` directory:
```
mkdir build
cd build
cmake ..
make
```

If, over the course of development, you ever encounter any problems building, a recommended method of troubleshooting is to first, delete the `build` directory you created above, and to retry building from scratch.

## Run the test
From the `code` directory:

First, follow the instructions to build the code as above.
Now you should be in a directory called `build`.
Simply execute the `headhunter` binary from that directory.
If all goes well, it should read in the example input file, and print out the id of the top k candidates it has picked.
