# What is the OPEN() function in C?
The open function allows you to OPEN a file (durr). It returns an FD, which is what is used to access the file.\
If the fd

**Prototype**\
`open(filename, flags)`

OPEN() has some specific flags:\
`O_RDONLY` Read Only\
`O_WRONLY` Write Only

If using READONLY, the OPEN() function only requires that flag.

`open(filename, O_RDONLY);` \
The write only also has some specific flags that go alongside it for this project:
```
O_CREAT 	Essential to create a file if it does not exist
O_TRUNC 	Essential to truncate a file
O_APPEND 	Essential to append to the end of the file
```
If you create a file, you also have to assign the permissions to it.\
Permissions are done in octal. In this project we are going to assign **0644**, as that is the standard new file default. That means that the created file will have the following permissions:\
`rw-r--r--`\
*Remember, in order, the permissions are **USER | GROUP | OTHERS***\
So, an example of an open function that is intended to write to, create (if needed), and truncate would be:\
`open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644)`\
and we would save the return of the function in an *int fd*, which would allow us to access the file via the fd.