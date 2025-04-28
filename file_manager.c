#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH_LENGTH 1000
#define MAX_LINE_LENGTH 1001  // 1000 chars + null terminator
#define MAX_LINES_PER_FILE 100

typedef struct {
    char *content;
    size_t length;
} Line;

typedef struct {
    char *path;
    Line *lines;
    int line_count;
} File;

// Function to read a line from file
char* read_line(FILE *fp) {
    char *line = malloc(MAX_LINE_LENGTH * sizeof(char));
    if (!line) {
        return NULL;
    }
    
    if (fgets(line, MAX_LINE_LENGTH, fp) == NULL) {
        free(line);
        return NULL;
    }
    
    // Remove newline character if present
    size_t len = strlen(line);
    if (len > 0 && *(line + len - 1) == '\n') {
        *(line + len - 1) = '\0';
        len--;
    }
    
    return line;
}

// Function to read file content
int read_file_content(File *file) {
    FILE *fp = fopen(file->path, "r");
    if (!fp) {
        return 0;
    }
    
    file->lines = malloc(MAX_LINES_PER_FILE * sizeof(Line));
    if (!file->lines) {
        fclose(fp);
        return 0;
    }
    
    file->line_count = 0;
    char *line_content;
    
    while ((line_content = read_line(fp)) != NULL && file->line_count < MAX_LINES_PER_FILE) {
        Line *current_line = file->lines + file->line_count;
        current_line->content = line_content;
        current_line->length = strlen(line_content);
        file->line_count++;
    }
    
    fclose(fp);
    return 1;
}

// Print file content separated by commas
void print_file(File *file) {
    for (int i = 0; i < file->line_count; i++) {
        printf("%s", (file->lines + i)->content);
        if (i < file->line_count - 1) {
            printf(",");
        }
    }
    printf("\n");
}

// Print all files content
void print_all_files(File *files, int file_count) {
    for (int i = 0; i < file_count; i++) {
        for (int j = 0; j < (files + i)->line_count; j++) {
            printf("%s", ((files + i)->lines + j)->content);
            if (j < (files + i)->line_count - 1) {
                printf(",");
            }
        }
        if (i < file_count - 1) {
            printf("\n");
        }
    }
    printf("\n");
}

// Find and print the longest string in a file
void print_longest_string(File *file) {
    if (file->line_count == 0) {
        printf("\n");
        return;
    }
    
    Line *longest_line = file->lines;
    
    for (int i = 1; i < file->line_count; i++) {
        if ((file->lines + i)->length > longest_line->length) {
            longest_line = file->lines + i;
        }
    }
    
    printf("%s\n", longest_line->content);
}

// Find and print the path of the longest file
void print_longest_file(File *files, int file_count) {
    if (file_count == 0) {
        printf("\n");
        return;
    }
    
    File *longest_file = files;
    
    for (int i = 1; i < file_count; i++) {
        if ((files + i)->line_count > longest_file->line_count) {
            longest_file = files + i;
        }
    }
    
    printf("%s\n", longest_file->path);
}

// Search for a string in all files
void search_string(File *files, int file_count, char *search_str) {
    for (int i = 0; i < file_count; i++) {
        for (int j = 0; j < (files + i)->line_count; j++) {
            if (strstr(((files + i)->lines + j)->content, search_str)) {
                printf("%s\n", (files + i)->path);
                return;
            }
        }
    }
}

// String comparison function for qsort
int compare_strings(const void *a, const void *b) {
    return strcmp(((Line *)a)->content, ((Line *)b)->content);
}

// Sort strings in a file
void sort_file(File *file) {
    qsort(file->lines, file->line_count, sizeof(Line), compare_strings);
}

// Remove all occurrences of a string from all files
void remove_string(File *files, int file_count, char *remove_str) {
    for (int i = 0; i < file_count; i++) {
        for (int j = 0; j < (files + i)->line_count; j++) {
            Line *current_line = (files + i)->lines + j;
            char *line_content = current_line->content;
            char *occurrence = strstr(line_content, remove_str);
            
            // If the string is found
            if (occurrence) {
                size_t remove_len = strlen(remove_str);
                size_t line_len = strlen(line_content);
                char *new_content = malloc(line_len + 1);
                
                if (new_content) {
                    int new_idx = 0;
                    size_t k = 0;  // Cambiado a size_t para coincidir con line_len
                    
                    // Check each character position
                    while (k < line_len) {
                        // If we found an occurrence here
                        if (line_content + k == occurrence) {
                            // Skip the characters of the string to remove
                            k += remove_len;
                            // Find the next occurrence (if any)
                            occurrence = strstr(line_content + k, remove_str);
                        } else {
                            // Copy the character
                            *(new_content + new_idx) = *(line_content + k);
                            new_idx++;
                            k++;
                        }
                    }
                    *(new_content + new_idx) = '\0';
                    
                    // Replace old content with new content
                    free(line_content);
                    current_line->content = new_content;
                    current_line->length = strlen(new_content);
                }
            }
        }
    }
}

// Append content of one file to another
void append_files(File *files, int idx1, int idx2) {
    File *file1 = files + idx1;
    File *file2 = files + idx2;
    
    // Ensure we don't exceed the maximum lines per file
    int total_lines = file1->line_count + file2->line_count;
    if (total_lines > MAX_LINES_PER_FILE) {
        total_lines = MAX_LINES_PER_FILE;
    }
    
    // Allocate new memory for combined lines if needed
    if (total_lines > file1->line_count) {
        Line *new_lines = realloc(file1->lines, total_lines * sizeof(Line));
        if (!new_lines) {
            return;
        }
        file1->lines = new_lines;
    }
    
    // Copy lines from file2 to file1
    int copied_lines = 0;
    for (int i = file1->line_count; i < total_lines; i++) {
        Line *src_line = file2->lines + copied_lines;
        Line *dest_line = file1->lines + i;
        
        // Deep copy the content
        dest_line->content = malloc(strlen(src_line->content) + 1);
        if (dest_line->content) {
            strcpy(dest_line->content, src_line->content);
            dest_line->length = src_line->length;
            copied_lines++;
        }
    }
    
    file1->line_count = file1->line_count + copied_lines;
}

// Execute commands from command file
void execute_commands(char *command_file_path, File *files, int file_count) {
    FILE *cmd_fp = fopen(command_file_path, "r");
    if (!cmd_fp) {
        return;
    }
    
    char *line = NULL;
    char *command = malloc(20 * sizeof(char));
    if (!command) {
        fclose(cmd_fp);
        return;
    }
    memset(command, 0, 20 * sizeof(char));
    
    while ((line = read_line(cmd_fp)) != NULL) {
        // Parse command
        if (sscanf(line, "%s", command) < 1) {
            free(line);
            continue;
        }
        
        if (strcmp(command, "PRINT") == 0) {
            int idx;
            if (sscanf(line, "%*s %d", &idx) < 1) {
                free(line);
                continue;
            }
            if (idx >= 0 && idx < file_count) {
                print_file(files + idx);
            }
        } else if (strcmp(command, "PRINT_ALL") == 0) {
            print_all_files(files, file_count);
        } else if (strcmp(command, "PRINT_LONGEST") == 0) {
            int idx;
            if (sscanf(line, "%*s %d", &idx) < 1) {
                free(line);
                continue;
            }
            if (idx >= 0 && idx < file_count) {
                print_longest_string(files + idx);
            }
        } else if (strcmp(command, "PRINT_LONGEST_FILE") == 0) {
            print_longest_file(files, file_count);
        } else if (strcmp(command, "SEARCH") == 0) {
            char *search_str = malloc(MAX_LINE_LENGTH * sizeof(char));
            if (!search_str) {
                free(line);
                continue;
            }
            memset(search_str, 0, MAX_LINE_LENGTH * sizeof(char));
            if (sscanf(line, "%*s %s", search_str) < 1) {
                free(search_str);
                free(line);
                continue;
            }
            search_string(files, file_count, search_str);
            free(search_str);
        } else if (strcmp(command, "SORT") == 0) {
            int idx;
            if (sscanf(line, "%*s %d", &idx) < 1) {
                free(line);
                continue;
            }
            if (idx >= 0 && idx < file_count) {
                sort_file(files + idx);
            }
        } else if (strcmp(command, "REMOVE") == 0) {
            char *remove_str = malloc(MAX_LINE_LENGTH * sizeof(char));
            if (!remove_str) {
                free(line);
                continue;
            }
            memset(remove_str, 0, MAX_LINE_LENGTH * sizeof(char));
            if (sscanf(line, "%*s %s", remove_str) < 1) {
                free(remove_str);
                free(line);
                continue;
            }
            remove_string(files, file_count, remove_str);
            free(remove_str);
        } else if (strcmp(command, "APPEND") == 0) {
            int idx1, idx2;
            if (sscanf(line, "%*s %d %d", &idx1, &idx2) < 2) {
                free(line);
                continue;
            }
            if (idx1 >= 0 && idx1 < file_count && idx2 >= 0 && idx2 < file_count) {
                append_files(files, idx1, idx2);
            }
        }
        
        free(line);
    }
    
    free(command);
    fclose(cmd_fp);
}

int main() {
    int file_count;
    if (scanf("%d\n", &file_count) != 1) {
        fprintf(stderr, "Error reading file count\n");
        return 1;
    }
    
    File *files = malloc(file_count * sizeof(File));
    if (!files) {
        return 1;
    }
    
    // Read file paths
    for (int i = 0; i < file_count; i++) {
        char *path = malloc(MAX_PATH_LENGTH * sizeof(char));
        if (!path) {
            // Free previously allocated memory
            for (int j = 0; j < i; j++) {
                free((files + j)->path);
            }
            free(files);
            return 1;
        }
        
        if (fgets(path, MAX_PATH_LENGTH, stdin) == NULL) {
            fprintf(stderr, "Error reading file path %d\n", i + 1);
            free(path);
            for (int j = 0; j < i; j++) {
                free((files + j)->path);
            }
            free(files);
            return 1;
        }
        
        size_t len = strlen(path);
        if (len > 0 && *(path + len - 1) == '\n') {
            *(path + len - 1) = '\0';
        }
        
        (files + i)->path = path;
        (files + i)->lines = NULL;
        (files + i)->line_count = 0;
    }
    
    // Read command file path
    char *command_file_path = malloc(MAX_PATH_LENGTH * sizeof(char));
    if (!command_file_path) {
        // Free allocated memory
        for (int i = 0; i < file_count; i++) {
            free((files + i)->path);
        }
        free(files);
        return 1;
    }
    
    if (fgets(command_file_path, MAX_PATH_LENGTH, stdin) == NULL) {
        fprintf(stderr, "Error reading command file path\n");
        free(command_file_path);
        for (int i = 0; i < file_count; i++) {
            free((files + i)->path);
        }
        free(files);
        return 1;
    }
    
    size_t len = strlen(command_file_path);
    if (len > 0 && *(command_file_path + len - 1) == '\n') {
        *(command_file_path + len - 1) = '\0';
    }
    
    // Read file contents
    for (int i = 0; i < file_count; i++) {
        if (!read_file_content(files + i)) {
            fprintf(stderr, "Error reading content of file %s\n", (files + i)->path);
        }
    }
    
    // Execute commands
    execute_commands(command_file_path, files, file_count);
    
    // Free allocated memory
    for (int i = 0; i < file_count; i++) {
        free((files + i)->path);
        for (int j = 0; j < (files + i)->line_count; j++) {
            free(((files + i)->lines + j)->content);
        }
        free((files + i)->lines);
    }
    free(files);
    free(command_file_path);
    
    return 0;
} 