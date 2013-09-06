#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "aalogparse.h"

int print_results(aa_log_record *record);

int main(int argc, char **argv)
{
	FILE *testcase;
	char log_line[1024];
	aa_log_record *test = NULL;
	int ret = -1;

	if (argc != 2)
	{
		fprintf(stderr, "Usage: test_multi.multi <filename>\n");
		return(1);
	}

	printf("START\n");
	printf("File: %s\n", argv[1]);

	testcase = fopen(argv[1], "r");
	if (testcase == NULL)
	{
		perror("Could not open testcase: ");
		return(1);
	}

	if (fgets(log_line, 1023, testcase) == NULL)
	{
		fprintf(stderr, "Could not read testcase.\n");
		fclose(testcase);
		return(1);
	}

	fclose(testcase);

	test = parse_record(log_line);

	if (test == NULL)
	{
		fprintf(stderr,"Parsing failed.\n");
		return(1);
	}
	ret = print_results(test);
	free_record(test);
	return ret;
}

#define print_string(description, var) \
	if ((var) != NULL) { \
		printf("%s: %s\n", (description), (var)); \
	}

/* unset is the value that the library sets to the var to indicate
   that it is unset */
#define print_long(description, var, unset) \
	if ((var) != (unsigned long) (unset)) { \
		printf("%s: %ld\n", (description), (var)); \
	}

int print_results(aa_log_record *record)
{
		printf("Event type: ");
		switch(record->event)
		{
			case AA_RECORD_ERROR:
			{
				printf("AA_RECORD_ERROR\n");
				break;
			}
			case AA_RECORD_INVALID:
			{
				printf("AA_RECORD_INVALID\n");
				break;
			}
			case AA_RECORD_AUDIT:
			{
				printf("AA_RECORD_AUDIT\n");
				break;
			}
			case AA_RECORD_ALLOWED:
			{
				printf("AA_RECORD_ALLOWED\n");
				break;
			}
			case AA_RECORD_DENIED:
			{
				printf("AA_RECORD_DENIED\n");
				break;
			}
			case AA_RECORD_HINT:
			{
				printf("AA_RECORD_HINT\n");
				break;
			}
			case AA_RECORD_STATUS:
			{
				printf("AA_RECORD_STATUS\n");
				break;
			}
			default:
			{
				printf("UNKNOWN EVENT TYPE\n");
				break;
			}
		}
		print_string("Audit ID", record->audit_id);
		print_string("Operation", record->operation);
		print_string("Mask", record->requested_mask);
		print_string("Denied Mask", record->denied_mask);

		print_long("fsuid", record->fsuid, (unsigned long) -1);
		print_long("ouid", record->ouid, (unsigned long) -1)

		print_string("Profile", record->profile);
		print_string("Peer profile", record->peer_profile);
		print_string("Name", record->name);
		print_string("Command", record->comm);
		print_string("Name2", record->name2);
		print_string("Namespace", record->namespace);
		print_string("Attribute", record->attribute);
		print_long("Task", record->task, 0);
		print_long("Parent", record->parent, 0);
		print_long("Token", record->magic_token, 0);
		print_string("Info", record->info);
		print_string("Peer info", record->peer_info);
		print_long("ErrorCode", (long) record->error_code, 0);
		print_long("PID", record->pid, 0);
		print_long("Peer PID", record->peer_pid, 0);
		print_string("Active hat", record->active_hat);

		print_string("Network family", record->net_family);
		print_string("Socket type", record->net_sock_type);
		print_string("Protocol", record->net_protocol);
		print_string("Local addr", record->net_local_addr);
		print_string("Foreign addr", record->net_foreign_addr);
		print_long("Local port", record->net_local_port, 0);
		print_long("Foreign port", record->net_foreign_port, 0);

		print_string("DBus bus", record->dbus_bus);
		print_string("DBus path", record->dbus_path);
		print_string("DBus interface", record->dbus_interface);
		print_string("DBus member", record->dbus_member);

		print_long("Epoch", record->epoch, 0);
		print_long("Audit subid", (long) record->audit_sub_id, 0);
	return(0);
}
