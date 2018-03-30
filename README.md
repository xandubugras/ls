# ls
Recreate the ls linux command with the flags -lrtaR
# Testing
Just run make && ./ft_ls [files or directories]
# How it works
- The main function sets the flags in the t_input struct and call ft_ls

- ft_ls is the big boss, it will control everything.
- starts out by creating a linked list of t_file (struct that contains info on files, directories, symlinks, etc)
- Now that we have a list containing all the files we will display, we order them properly using bubble sort
- with the list ordered, we set all the files that may go into recursion, and then go into those directories.
- frees everything.

For more info regarding how the code works, you may check the comments written above all important functions
