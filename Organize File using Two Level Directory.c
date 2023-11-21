#include <stdio.h>
#include <string.h>

void main() {
    char dir[100];
    printf("Enter directory name: ");
    scanf("%s", dir);

    if (mkdir(dir, 0777) != 0) {
        printf("Directory already exists.\n");
        return;
    }

    char subdir[100];
    int i;
    for (i = 0; i < 10; i++) {
        sprintf(subdir, "%s/Subdir_%d", dir, i);
        mkdir(subdir, 0777);
    }

    printf("Directory and subdirectories created successfully.\n");
}
