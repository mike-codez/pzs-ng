#!/bin/bash

################################################
# Please do not edit below                     #
################################################

audiogenres="A cappella
Acid
Acid Jazz
Acid Punk
Acoustic
Alternative
AlternRock
Ambient
Anime
Avantgarde
Ballad
Bass
Beat
Bebob
Big Band
Black Metal
Bluegrass
Blues
Booty Bass
BritPop
Cabaret
Celtic
Chamber Music
Chanson
Chorus
Christian Gangsta Rap
Christian Rap
Christian Rock
Classic Rock
Classical
Club
Club-House
Comedy
Contemporary Christian
Country
Crossover
Cult
Dance
Dance Hall
Darkwave
Death Metal
Disco
Dream
Drum & Bass
Drum Solo
Duet
Easy Listening
Electronic
Ethnic
Euro-House
Euro-Techno
Eurodance
Fast Fusion
Folk
Folk-Rock
Folklore
Freestyle
Funk
Fusion
Game
Gangsta
Goa
Gospel
Gothic
Gothic Rock
Grunge
Hard Rock
Hardcore
Heavy Metal
Hip-Hop
House
Humour
Indie
Industrial
Instrumental
Instrumental Pop
Instrumental Rock
Jazz
Jazz+Funk
JPop
Jungle
Latin
Lo-Fi
Meditative
Merengue
Metal
Musical
National Folk
Native American
Negerpunk
New Age
New Wave
Noise
Oldies
Opera
Other
Polka
Polsk Punk
Pop
Pop-Folk
Pop_Funk
Porn Groove
Power Ballad
Pranks
Primus
Progressive Rock
Psychedelic
Psychedelic Rock
Punk
Punk Rock
R&B
Rap
Rave
Reggae
Retro
Revival
Rhythmic Soul
Rock
Rock & Roll
Salsa
Samba
Satire
Showtunes
Ska
Slow Jam
Slow Rock
Sonata
Soul
Sound Clip
Soundtrack
Southern Rock
Space
Speech
Swing
Symphonic Rock
Symphony
Synthpop
Tango
Techno
Techno-Industrial
Terror
Thrash Metal
Top 40
Trailer
Trance
Tribal
Trip-Hop
Unknown
Vocal"

possible_glroot_paths="/glftpd /jail/glftpd /usr/glftpd /usr/jail/glftpd /usr/local/glftpd /usr/local/jail/glftpd /$HOME/glftpd /glftpd/glftpd /opt/glftpd"
if [ $# -eq 0 ]; then
	for possible_glroot in $possible_glroot_paths; do
		if [ -e ${possible_glroot}/etc/group ]; then
		glroot=${possible_glroot}
		break
		fi
	done

	if [ -z ${glroot} ]; then
		echo ""
		echo "Usage: $0 /path/to/glftpd-root-dir"
		echo ""
		exit 0
	fi
else
	glroot=$1
	if [ ! -e /$glroot/etc/group ]; then
		echo ""
		echo "Oops! I think you wrote wrong path. I can't find"
		echo "$glroot/etc/group - Exiting."
		exit 0
	fi
fi

groupfile=$glroot/etc/group

echo "This program fills glftpd's group file with valid audio-genre names."
echo "This is needed to be able to use the ng-chown script as an audio-genre script."
echo ""
echo "groupfile to edit: $groupfile"
echo ""
echo "press <enter> to continue, or <ctrl-c> to break off."
read line
echo "making backup of $groupfile -> $groupfile.bak"
cp $groupfile $groupfile.bak
echo "Working..."

IFSBAK="$IFS"
IFS="
"

for genreorig in $audiogenres; do
  genre="`echo "$genreorig" | tr ' ' '_'`"
  if [ -z "`grep -e "^$genre:" $groupfile`" ]; then
    gid=`tail -n 1 $groupfile | cut -d ':' -f 3`
    let gid=gid+100
    echo "$genre:$genre:$gid:AUDIO-GENRE" >> $groupfile
    echo "Adding genre '$genre' with gid '$gid'"
  fi
done

IFS=$IFSBAK

echo ""
echo "To make use of the audio genres, add the following in you zsconfig.h:"
echo ""
echo "#define enable_audio_script             TRUE"
echo "#define audio_script                    \"/bin/ng-chown\""
echo "#define audio_script_cookies            \"0 0 0 1 0 1 - \\\"%w\\\" \\\"%?\\\"\""
echo "#define allow_gid_change_in_ng_chown    TRUE"
echo "#define allow_dir_chown_in_ng_chown     TRUE"
echo ""
echo "Then 'make install' as usual, and chmod +s ng-chown:"
echo "  chmod +s $glroot/bin/ng-chown"
echo ""
echo "A backup of the original groupfile is located at:"
echo "  $groupfile.bak"
exit 0

