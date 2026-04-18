#include <ctype.h>
#include <dirent.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#ifdef _WIN32
    #include <direct.h>
    #define mkdir(path, mode) _mkdir(path)
#else
    #include <sys/stat.h>
#endif

int organize_preview_files (char *folder, int preview);

int main (int argc, char *argv[])
{
    // Handle user input incorrectness
    if (argc < 2 || argc > 4)
    {
        printf("Usage: ./organizer /folder\n");
        printf("       ./organizer --preview /folder\n");
        return 1;
    }

    int returnOrganize = 0;
    
    if (argc == 3)
    {
        if (strcmp(argv[1], "--preview") == 0)
        {
            returnOrganize = organize_preview_files(argv[2], 1);
            return returnOrganize;
        }
        else
        {
            printf("Usage: ./organizer /folder\n");
            printf("       ./organizer --preview /folder\n");
            return 1;
        }
    }
    else
    {
        returnOrganize = organize_preview_files(argv[1], 0);
        return returnOrganize;
    }
}

// Organize/Preview files in directory
int organize_preview_files (char *folder, int preview)
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

    if (preview)
    {
        printf("Preview: %s\n", folder);
    }
    else
    {
        printf("Organizing: %s\n", folder);
    }

    // Organize every file to dedicated folder or preview changes to directory
    while ((entry = readdir(mainFolder)) != NULL)
    {
        char *ext = strrchr(entry->d_name, '.');
        char dest[PATH_MAX * 2];
        char dir_path[PATH_MAX];
        char src[PATH_MAX];
        char *category;
        char ext_lower[16];

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

        // Make ext lowercase for sorting in categories
        if (ext == NULL)
        {
            ext_lower[0] = '\0';
        }
        else
        {
            for (int i = 0; ext[i]; i++)
            {
                ext_lower[i] = tolower(ext[i]);
            }
            ext_lower[strlen(ext)] = '\0';
        }

        if (ext == NULL)
        {
            category = "Other";
        }
        else if (strcmp(ext_lower, ".jpg") == 0 || 
                 strcmp(ext_lower, ".jpeg") == 0 || 
                 strcmp(ext_lower, ".png") == 0)
        {
            category = "Images";
        }
        else if (strcmp(ext_lower, ".pdf") == 0 || 
                 strcmp(ext_lower, ".doc") == 0 || 
                 strcmp(ext_lower, ".docx") == 0 ||
                 strcmp(ext_lower, ".xls") == 0 ||
                 strcmp(ext_lower, ".xlsx") == 0 ||
                 strcmp(ext_lower, ".ppt") == 0 ||
                 strcmp(ext_lower, ".pptx") == 0 ||
                 strcmp(ext_lower, ".odt") == 0 ||
                 strcmp(ext_lower, ".txt") == 0 ||
                 strcmp(ext_lower, ".rtf") == 0)
        {
            category = "Documents";
        }
        else if (strcmp(ext_lower, ".mp3") == 0 || 
                 strcmp(ext_lower, ".wav") == 0 ||
                 strcmp(ext_lower, ".m4a") == 0)
        {
            category = "Music";
        }
        else if (strcmp(ext_lower, ".mp4") == 0 || 
                 strcmp(ext_lower, ".mov") == 0 || 
                 strcmp(ext_lower, ".mkv") == 0 ||
                 strcmp(ext_lower, ".wmv") == 0)
        {
            category = "Videos";
        }
        else if (strcmp(ext_lower, ".py") == 0 || 
                 strcmp(ext_lower, ".java") == 0 || 
                 strcmp(ext_lower, ".c") == 0 ||
                 strcmp(ext_lower, ".cpp") == 0 ||
                 strcmp(ext_lower, ".cc") == 0 ||
                 strcmp(ext_lower, ".cs") == 0 ||
                 strcmp(ext_lower, ".swift") == 0 ||
                 strcmp(ext_lower, ".go") == 0 ||
                 strcmp(ext_lower, ".rs") == 0 ||
                 strcmp(ext_lower, ".js") == 0)
        {
            category = "Code";
        }
        else
        {
            category = "Other";  // catch all unrecognized extensions
        }

        // Build directory path for both organize mode and preview mode
        sprintf(dir_path, "%s/%s", folder, category);

        if (preview)
        {
            // Preview changes in directory
            printf(" %s -> %s\n", entry->d_name, dir_path);
        }
        else
        {
            // Organize files in directory
            mkdir(dir_path, 0777);
            sprintf(src, "%s/%s", folder, entry->d_name);
            snprintf(dest, PATH_MAX * 2, "%s/%s", dir_path, entry->d_name);
            // Prevent file overwrite
            if (access(dest, F_OK) == 0)
            {
                // Strip ext from entry->d_name
                int name_len = ext - entry->d_name;
                char name[256];
                strncpy(name, entry->d_name, name_len);
                name[name_len] = '\0';

                // Rename file as a copy (1), (2)...(12), e.t.c
                int n = 1;
                char new_dest[PATH_MAX * 2];
                do
                {
                    sprintf(new_dest, "%s/%s (%d)%s", dir_path, name, n, ext);
                    n++;
                } while (access(new_dest, F_OK) == 0);
                rename(src, new_dest);
                char new_name[PATH_MAX];
                sprintf(new_name, "%s (%d)%s", name, n - 1, ext);
                printf(" %s -> %s   (renamed: %s)\n", entry->d_name, dir_path, new_name);
            }
            else
            {
                rename(src, dest);
                printf(" %s -> %s\n", entry->d_name, dir_path);
            }
        }

        count++;
    }

    if (empty == 1)
    {
        printf("Directory has no files!\n");
        closedir(mainFolder);
        return 3;
    }

    if (preview)
    {
        printf("Preview: would organize %i files!\n", count);
    }
    else
    {
        printf("Successfully organized %i files!\n", count);
    }

    closedir(mainFolder);
    return 0;
}