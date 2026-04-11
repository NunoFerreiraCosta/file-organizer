#include <dirent.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

int organize_files (char *folder);

int main (int argc, char *argv[])
{
    // Handle user input incorrectness
    if (argc < 2 || argc > 4)
    {
        printf("Usage: ./organizer /folder\n");
        printf("       ./organizer --preview /folder\n");
        return 1;
    }

    // Preview mode TODO
    if (argc == 3)
    {
        // Handle user input incorrectness
        if (strcmp(argv[1], "--preview") != 0)
        {
            printf("Usage: ./organizer /folder\n");
            printf("       ./organizer --preview /folder\n");
            return 1;
        }

        // TODO
    }

    int returnOrganize = organize_files(argv[1]);
    return returnOrganize;
}

int organize_files (char *folder)
{
    // Open prompted folder and handle error
    DIR *mainFolder = opendir(folder);
    if (mainFolder == NULL)
    {
        printf("Could not open directory!\n");
        return 2;
    }

    struct dirent *entry;
    int empty = 1;
    int count = 0;

    printf("Organizing: %s\n", folder);

    // Organize every file to dedicated folder
    while ((entry = readdir(mainFolder)) != NULL)
    {
        char *ext = strrchr(entry->d_name, '.');
        char dest[PATH_MAX * 2];
        char dir_path[PATH_MAX];
        char src[PATH_MAX];
        char *category;

        // skip . and ..
        if (entry->d_name[0] == '.')
        {
            continue;
        }

        // Skip folder
        if (entry->d_type == DT_DIR)
        {
            continue;
        }

        // If found file otherwise empty will still be 1
        empty = 0;

        if (ext == NULL)
        {
            category = "Other";
        }
        else if (strcmp(ext, ".jpg") == 0 || 
                 strcmp(ext, ".jpeg") == 0 || 
                 strcmp(ext, ".png") == 0)
        {
            category = "Images";
        }
        else if (strcmp(ext, ".pdf") == 0 || 
                 strcmp(ext, ".doc") == 0 || 
                 strcmp(ext, ".docx") == 0 ||
                 strcmp(ext, ".xls") == 0 ||
                 strcmp(ext, ".xlsx") == 0 ||
                 strcmp(ext, ".ppt") == 0 ||
                 strcmp(ext, ".pptx") == 0 ||
                 strcmp(ext, ".odt") == 0 ||
                 strcmp(ext, ".txt") == 0 ||
                 strcmp(ext, ".rtf") == 0)
        {
            category = "Documents";
        }
        else if (strcmp(ext, ".mp3") == 0 || strcmp(ext, ".wav") == 0)
        {
            category = "Music";
        }
        else if (strcmp(ext, ".mp4") == 0 || 
                 strcmp(ext, ".mov") == 0 || 
                 strcmp(ext, ".mkv") == 0 ||
                 strcmp(ext, ".wmv") == 0)
        {
            category = "Videos";
        }
        else if (strcmp(ext, ".py") == 0 || 
                 strcmp(ext, ".java") == 0 || 
                 strcmp(ext, ".c") == 0 ||
                 strcmp(ext, ".cpp") == 0 ||
                 strcmp(ext, ".cc") == 0 ||
                 strcmp(ext, ".cs") == 0 ||
                 strcmp(ext, ".swift") == 0 ||
                 strcmp(ext, ".go") == 0 ||
                 strcmp(ext, ".rs") == 0 ||
                 strcmp(ext, ".js") == 0)
        {
            category = "Code";
        }
        else
        {
            category = "Other";  // catch all unrecognized extensions
        }

        sprintf(dir_path, "%s/%s", folder, category);
        mkdir(dir_path, 0777);
        sprintf(src, "%s/%s", folder, entry->d_name);
        snprintf(dest, PATH_MAX * 2, "%s/%s", dir_path, entry->d_name);
        rename(src, dest);

        printf(" %s -> %s\n", entry->d_name, dir_path);
        count++;
    }

    if (empty == 1)
    {
        printf("Directory has no files!\n");
        closedir(mainFolder);
        return 3;
    }

    printf("Successfully organized %i files!\n", count);

    closedir(mainFolder);
    return 0;
}