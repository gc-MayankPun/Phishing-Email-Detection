#include <stdio.h>
#include <string.h>

typedef struct {
    char from[256];
    char reply_to[256];
    char subject[256];
    char body[10000];
} Email;

int parse_email(const char *filename, Email *email) {

    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file\n");
        return 1;
    }

    char line[1024];
    int body_started = 0;

    memset(email, 0, sizeof(Email));

    while (fgets(line, sizeof(line), file)) {

        line[strcspn(line, "\n")] = 0;

        if (!body_started) {

            if (strncmp(line, "From:", 5) == 0)
                strcpy(email->from, line + 6);

            else if (strncmp(line, "Reply-To:", 9) == 0)
                strcpy(email->reply_to, line + 10);

            else if (strncmp(line, "Subject:", 8) == 0)
                strcpy(email->subject, line + 9);

            else if (strlen(line) == 0)
                body_started = 1;

        } else {
            strcat(email->body, line);
            strcat(email->body, "\n");
        }
    }

    fclose(file);
    return 0;
}

int main(int argc, char *argv[]) {

    if (argc != 2) {
        printf("Usage: %s <email_file>\n", argv[0]);
        return 1;
    }

    Email email;

    if (parse_email(argv[1], &email) != 0)
        return 1;

    printf("From: %s\n", email.from);
    printf("Reply-To: %s\n", email.reply_to);
    printf("Subject: %s\n", email.subject);
    printf("\nBody:\n%s\n", email.body);

    return 0;
}
