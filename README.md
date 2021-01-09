# Study of Web graphs
School project developed using CPP.

## Installing dependencies for python plotting!
```bash
    # Navigate to the Plotting directory
    $ cd GraphesOCA/Plotting

    # Create the virtual environement (venv)
    $ python3 -m venv venv

    # Install required python modules
    (venv)$ pip install -r requirements.txt
``` 

## Building CPP project
Use CMake to build the project.
```bash
    $ cd GraphesOCA
    $ mkdir build
    $ cd build
    $ cmake ..
    $ make
``` 

## Executing
### Part 1
Executing the CPP binary to extract data from the graphs database.
```bash
    $ cd GraphesOCA/build
    $ ./GraphesOCA
```

### Part 2
Executing the Python script to make the plots (charts).

***Keep in mind that this part requires the installed dependencies mentionned above!***
```bash
    $ cd GraphesOCA/Plotting

    # Activating the virtual environment
    $ source venv/bin/activate

    # Executing the script
    (venv)$ python plot.py

    # Deactivating the virtual environment
    (venv)$ deactivate
    
```

Managing the development tasks in a [Trello Table](https://trello.com/c/cTMhD2zT/11-outils-pour-conception-dalgorithmes).
