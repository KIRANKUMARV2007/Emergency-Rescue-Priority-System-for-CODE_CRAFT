
#include <stdio.h>
#include <string.h>

struct RescueRequest {
    char requestID[20];
    char location[50];
    int people;
    char emergency[20];
    char resources[50];
    char assignedTeam[30];
    char status[20];
    int priority;
};

int main() {
    struct RescueRequest r[100], temp;
    FILE *fp;
    int count, i, j, found;
    char searchID[20];
    char newStatus[20];

    printf("===== EMERGENCY RESCUE PRIORITY SYSTEM =====\n");
    printf("Enter number of rescue requests (1-100): ");

    if (scanf("%d", &count) != 1 || count < 1 || count > 100) {
        printf("Invalid number of requests!\n");
        return 1;
    }

    for (i = 0; i < count; i++) {
        printf("\nEnter details for Request %d\n", i + 1);

        printf("Request ID: ");
        scanf("%19s", r[i].requestID);

        printf("Location: ");
        scanf(" %49[^\n]", r[i].location);

        printf("Number of people affected: ");
        if (scanf("%d", &r[i].people) != 1 || r[i].people < 0) {
            printf("Invalid number of people!\n");
            return 1;
        }

        printf("Emergency type (Critical/High/Normal): ");
        scanf("%19s", r[i].emergency);

        if (strcmp(r[i].emergency, "Critical") == 0 ||
            strcmp(r[i].emergency, "critical") == 0) {
            strcpy(r[i].emergency, "Critical");
            r[i].priority = 1;
        } else if (strcmp(r[i].emergency, "High") == 0 ||
                   strcmp(r[i].emergency, "high") == 0) {
            strcpy(r[i].emergency, "High");
            r[i].priority = 2;
        } else if (strcmp(r[i].emergency, "Normal") == 0 ||
                   strcmp(r[i].emergency, "normal") == 0) {
            strcpy(r[i].emergency, "Normal");
            r[i].priority = 3;
        } else {
            printf("Invalid emergency type! Use Critical, High, or Normal.\n");
            return 1;
        }

        printf("Required resources: ");
        scanf(" %49[^\n]", r[i].resources);

        strcpy(r[i].assignedTeam, "NotAssigned");
        strcpy(r[i].status, "Pending");
    }

    /* Sort requests by priority */
    for (i = 0; i < count - 1; i++) {
        for (j = 0; j < count - i - 1; j++) {
            if (r[j].priority > r[j + 1].priority) {
                temp = r[j];
                r[j] = r[j + 1];
                r[j + 1] = temp;
            }
        }
    }

    printf("\n===== REQUESTS SORTED BY PRIORITY =====\n");

    for (i = 0; i < count; i++) {
        printf("\nID: %s\n", r[i].requestID);
        printf("Location: %s\n", r[i].location);
        printf("People affected: %d\n", r[i].people);
        printf("Emergency: %s\n", r[i].emergency);
        printf("Resources: %s\n", r[i].resources);
        printf("Priority: %d\n", r[i].priority);
        printf("Assigned Team: %s\n", r[i].assignedTeam);
        printf("Status: %s\n", r[i].status);
    }

    /* Assign rescue team */
    printf("\nEnter Request ID to assign a team: ");
    scanf("%19s", searchID);

    found = 0;

    for (i = 0; i < count; i++) {
        if (strcmp(r[i].requestID, searchID) == 0) {
            printf("Enter rescue team name (no spaces): ");
            scanf("%29s", r[i].assignedTeam);
            strcpy(r[i].status, "InProgress");
            found = 1;
            printf("Team assigned successfully!\n");
            break;
        }
    }

    if (!found) {
        printf("Request ID not found!\n");
    }

    /* Update status */
    printf("\nEnter Request ID to update status: ");
    scanf("%19s", searchID);

    found = 0;

    for (i = 0; i < count; i++) {
        if (strcmp(r[i].requestID, searchID) == 0) {
            while (1) {
                printf("Enter status (Pending/InProgress/Resolved): ");
                scanf("%19s", newStatus);

                if (strcmp(newStatus, "Pending") == 0 ||
                    strcmp(newStatus, "pending") == 0) {
                    strcpy(r[i].status, "Pending");
                    break;
                } else if (strcmp(newStatus, "InProgress") == 0 ||
                           strcmp(newStatus, "inprogress") == 0) {
                    strcpy(r[i].status, "InProgress");
                    break;
                } else if (strcmp(newStatus, "Resolved") == 0 ||
                           strcmp(newStatus, "resolved") == 0) {
                    strcpy(r[i].status, "Resolved");
                    break;
                } else {
                    printf("Invalid status! Try again.\n");
                }
            }

            found = 1;
            printf("Status updated successfully!\n");
            break;
        }
    }

    if (!found) {
        printf("Request ID not found!\n");
    }

    /* Search request */
    printf("\nEnter Request ID to search: ");
    scanf("%19s", searchID);

    found = 0;

    for (i = 0; i < count; i++) {
        if (strcmp(r[i].requestID, searchID) == 0) {
            printf("\n===== REQUEST FOUND =====\n");
            printf("ID: %s\n", r[i].requestID);
            printf("Location: %s\n", r[i].location);
            printf("People affected: %d\n", r[i].people);
            printf("Emergency: %s\n", r[i].emergency);
            printf("Resources: %s\n", r[i].resources);
            printf("Team: %s\n", r[i].assignedTeam);
            printf("Status: %s\n", r[i].status);
            printf("Priority: %d\n", r[i].priority);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Request ID not found!\n");
    }

    /* Emergency summary */
    {
        int critical = 0, high = 0, normal = 0;
        int pending = 0, inProgress = 0, resolved = 0;

        for (i = 0; i < count; i++) {
            if (r[i].priority == 1)
                critical++;
            else if (r[i].priority == 2)
                high++;
            else
                normal++;

            if (strcmp(r[i].status, "Pending") == 0)
                pending++;
            else if (strcmp(r[i].status, "InProgress") == 0)
                inProgress++;
            else if (strcmp(r[i].status, "Resolved") == 0)
                resolved++;
        }

        printf("\n===== EMERGENCY SUMMARY =====\n");
        printf("Total requests: %d\n", count);
        printf("Critical: %d\n", critical);
        printf("High: %d\n", high);
        printf("Normal: %d\n", normal);
        printf("Pending: %d\n", pending);
        printf("In Progress: %d\n", inProgress);
        printf("Resolved: %d\n", resolved);
    }

    /* Save final updated data */
    fp = fopen("rescue.txt", "w");

    if (fp == NULL) {
        printf("\nCould not save requests to file!\n");
        return 1;
    }

    fprintf(fp, "ID|Location|People|Emergency|Resources|Team|Priority|Status\n");

    for (i = 0; i < count; i++) {
        fprintf(fp, "%s|%s|%d|%s|%s|%s|%d|%s\n",
                r[i].requestID,
                r[i].location,
                r[i].people,
                r[i].emergency,
                r[i].resources,
                r[i].assignedTeam,
                r[i].priority,
                r[i].status);
    }

    fclose(fp);

    printf("\nAll requests saved to rescue.txt successfully!\n");

    return 0;
}
