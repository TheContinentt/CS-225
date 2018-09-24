#!/bin/sh
# This script was generated using Makeself 2.3.0

ORIG_UMASK=`umask`
if test "n" = n; then
    umask 077
fi

CRCsum="292469514"
MD5="6ef9c5b8f69ef7e326b3bb4454318fb1"
TMPROOT=${TMPDIR:=/tmp}
USER_PWD="$PWD"; export USER_PWD

label="Problem of the Day #3"
script="echo"
scriptargs=""
licensetxt=""
helpheader=''
targetdir="potd-q3"
filesizes="77855"
keep="y"
nooverwrite="n"
quiet="n"
nodiskspace="n"

print_cmd_arg=""
if type printf > /dev/null; then
    print_cmd="printf"
elif test -x /usr/ucb/echo; then
    print_cmd="/usr/ucb/echo"
else
    print_cmd="echo"
fi

unset CDPATH

MS_Printf()
{
    $print_cmd $print_cmd_arg "$1"
}

MS_PrintLicense()
{
  if test x"$licensetxt" != x; then
    echo "$licensetxt"
    while true
    do
      MS_Printf "Please type y to accept, n otherwise: "
      read yn
      if test x"$yn" = xn; then
        keep=n
	eval $finish; exit 1
        break;
      elif test x"$yn" = xy; then
        break;
      fi
    done
  fi
}

MS_diskspace()
{
	(
	if test -d /usr/xpg4/bin; then
		PATH=/usr/xpg4/bin:$PATH
	fi
	df -kP "$1" | tail -1 | awk '{ if ($4 ~ /%/) {print $3} else {print $4} }'
	)
}

MS_dd()
{
    blocks=`expr $3 / 1024`
    bytes=`expr $3 % 1024`
    dd if="$1" ibs=$2 skip=1 obs=1024 conv=sync 2> /dev/null | \
    { test $blocks -gt 0 && dd ibs=1024 obs=1024 count=$blocks ; \
      test $bytes  -gt 0 && dd ibs=1 obs=1024 count=$bytes ; } 2> /dev/null
}

MS_dd_Progress()
{
    if test x"$noprogress" = xy; then
        MS_dd $@
        return $?
    fi
    file="$1"
    offset=$2
    length=$3
    pos=0
    bsize=4194304
    while test $bsize -gt $length; do
        bsize=`expr $bsize / 4`
    done
    blocks=`expr $length / $bsize`
    bytes=`expr $length % $bsize`
    (
        dd ibs=$offset skip=1 2>/dev/null
        pos=`expr $pos \+ $bsize`
        MS_Printf "     0%% " 1>&2
        if test $blocks -gt 0; then
            while test $pos -le $length; do
                dd bs=$bsize count=1 2>/dev/null
                pcent=`expr $length / 100`
                pcent=`expr $pos / $pcent`
                if test $pcent -lt 100; then
                    MS_Printf "\b\b\b\b\b\b\b" 1>&2
                    if test $pcent -lt 10; then
                        MS_Printf "    $pcent%% " 1>&2
                    else
                        MS_Printf "   $pcent%% " 1>&2
                    fi
                fi
                pos=`expr $pos \+ $bsize`
            done
        fi
        if test $bytes -gt 0; then
            dd bs=$bytes count=1 2>/dev/null
        fi
        MS_Printf "\b\b\b\b\b\b\b" 1>&2
        MS_Printf " 100%%  " 1>&2
    ) < "$file"
}

MS_Help()
{
    cat << EOH >&2
${helpheader}Makeself version 2.3.0
 1) Getting help or info about $0 :
  $0 --help   Print this message
  $0 --info   Print embedded info : title, default target directory, embedded script ...
  $0 --lsm    Print embedded lsm entry (or no LSM)
  $0 --list   Print the list of files in the archive
  $0 --check  Checks integrity of the archive

 2) Running $0 :
  $0 [options] [--] [additional arguments to embedded script]
  with following options (in that order)
  --confirm             Ask before running embedded script
  --quiet		Do not print anything except error messages
  --noexec              Do not run embedded script
  --keep                Do not erase target directory after running
			the embedded script
  --noprogress          Do not show the progress during the decompression
  --nox11               Do not spawn an xterm
  --nochown             Do not give the extracted files to the current user
  --nodiskspace         Do not check for available disk space
  --target dir          Extract directly to a target directory
                        directory path can be either absolute or relative
  --tar arg1 [arg2 ...] Access the contents of the archive through the tar command
  --                    Following arguments will be passed to the embedded script
EOH
}

MS_Check()
{
    OLD_PATH="$PATH"
    PATH=${GUESS_MD5_PATH:-"$OLD_PATH:/bin:/usr/bin:/sbin:/usr/local/ssl/bin:/usr/local/bin:/opt/openssl/bin"}
	MD5_ARG=""
    MD5_PATH=`exec <&- 2>&-; which md5sum || command -v md5sum || type md5sum`
    test -x "$MD5_PATH" || MD5_PATH=`exec <&- 2>&-; which md5 || command -v md5 || type md5`
	test -x "$MD5_PATH" || MD5_PATH=`exec <&- 2>&-; which digest || command -v digest || type digest`
    PATH="$OLD_PATH"

    if test x"$quiet" = xn; then
		MS_Printf "Verifying archive integrity..."
    fi
    offset=`head -n 531 "$1" | wc -c | tr -d " "`
    verb=$2
    i=1
    for s in $filesizes
    do
		crc=`echo $CRCsum | cut -d" " -f$i`
		if test -x "$MD5_PATH"; then
			if test x"`basename $MD5_PATH`" = xdigest; then
				MD5_ARG="-a md5"
			fi
			md5=`echo $MD5 | cut -d" " -f$i`
			if test x"$md5" = x00000000000000000000000000000000; then
				test x"$verb" = xy && echo " $1 does not contain an embedded MD5 checksum." >&2
			else
				md5sum=`MS_dd_Progress "$1" $offset $s | eval "$MD5_PATH $MD5_ARG" | cut -b-32`;
				if test x"$md5sum" != x"$md5"; then
					echo "Error in MD5 checksums: $md5sum is different from $md5" >&2
					exit 2
				else
					test x"$verb" = xy && MS_Printf " MD5 checksums are OK." >&2
				fi
				crc="0000000000"; verb=n
			fi
		fi
		if test x"$crc" = x0000000000; then
			test x"$verb" = xy && echo " $1 does not contain a CRC checksum." >&2
		else
			sum1=`MS_dd_Progress "$1" $offset $s | CMD_ENV=xpg4 cksum | awk '{print $1}'`
			if test x"$sum1" = x"$crc"; then
				test x"$verb" = xy && MS_Printf " CRC checksums are OK." >&2
			else
				echo "Error in checksums: $sum1 is different from $crc" >&2
				exit 2;
			fi
		fi
		i=`expr $i + 1`
		offset=`expr $offset + $s`
    done
    if test x"$quiet" = xn; then
		echo " All good."
    fi
}

UnTAR()
{
    if test x"$quiet" = xn; then
		tar $1vf - 2>&1 || { echo Extraction failed. > /dev/tty; kill -15 $$; }
    else

		tar $1f - 2>&1 || { echo Extraction failed. > /dev/tty; kill -15 $$; }
    fi
}

finish=true
xterm_loop=
noprogress=n
nox11=n
copy=none
ownership=y
verbose=n

initargs="$@"

while true
do
    case "$1" in
    -h | --help)
	MS_Help
	exit 0
	;;
    -q | --quiet)
	quiet=y
	noprogress=y
	shift
	;;
    --info)
	echo Identification: "$label"
	echo Target directory: "$targetdir"
	echo Uncompressed size: 432 KB
	echo Compression: gzip
	echo Date of packaging: Thu Sep  7 07:52:00 CDT 2017
	echo Built with Makeself version 2.3.0 on linux-gnu
	echo Build command was: "./makeself.sh \\
    \"--notemp\" \\
    \"potd-q3\" \\
    \"potd-q3.sh\" \\
    \"Problem of the Day #3\" \\
    \"echo\""
	if test x"$script" != x; then
	    echo Script run after extraction:
	    echo "    " $script $scriptargs
	fi
	if test x"" = xcopy; then
		echo "Archive will copy itself to a temporary location"
	fi
	if test x"n" = xy; then
		echo "Root permissions required for extraction"
	fi
	if test x"y" = xy; then
	    echo "directory $targetdir is permanent"
	else
	    echo "$targetdir will be removed after extraction"
	fi
	exit 0
	;;
    --dumpconf)
	echo LABEL=\"$label\"
	echo SCRIPT=\"$script\"
	echo SCRIPTARGS=\"$scriptargs\"
	echo archdirname=\"potd-q3\"
	echo KEEP=y
	echo NOOVERWRITE=n
	echo COMPRESS=gzip
	echo filesizes=\"$filesizes\"
	echo CRCsum=\"$CRCsum\"
	echo MD5sum=\"$MD5\"
	echo OLDUSIZE=432
	echo OLDSKIP=532
	exit 0
	;;
    --lsm)
cat << EOLSM
No LSM.
EOLSM
	exit 0
	;;
    --list)
	echo Target directory: $targetdir
	offset=`head -n 531 "$0" | wc -c | tr -d " "`
	for s in $filesizes
	do
	    MS_dd "$0" $offset $s | eval "gzip -cd" | UnTAR t
	    offset=`expr $offset + $s`
	done
	exit 0
	;;
	--tar)
	offset=`head -n 531 "$0" | wc -c | tr -d " "`
	arg1="$2"
    if ! shift 2; then MS_Help; exit 1; fi
	for s in $filesizes
	do
	    MS_dd "$0" $offset $s | eval "gzip -cd" | tar "$arg1" - "$@"
	    offset=`expr $offset + $s`
	done
	exit 0
	;;
    --check)
	MS_Check "$0" y
	exit 0
	;;
    --confirm)
	verbose=y
	shift
	;;
	--noexec)
	script=""
	shift
	;;
    --keep)
	keep=y
	shift
	;;
    --target)
	keep=y
	targetdir=${2:-.}
    if ! shift 2; then MS_Help; exit 1; fi
	;;
    --noprogress)
	noprogress=y
	shift
	;;
    --nox11)
	nox11=y
	shift
	;;
    --nochown)
	ownership=n
	shift
	;;
    --nodiskspace)
	nodiskspace=y
	shift
	;;
    --xwin)
	if test "n" = n; then
		finish="echo Press Return to close this window...; read junk"
	fi
	xterm_loop=1
	shift
	;;
    --phase2)
	copy=phase2
	shift
	;;
    --)
	shift
	break ;;
    -*)
	echo Unrecognized flag : "$1" >&2
	MS_Help
	exit 1
	;;
    *)
	break ;;
    esac
done

if test x"$quiet" = xy -a x"$verbose" = xy; then
	echo Cannot be verbose and quiet at the same time. >&2
	exit 1
fi

if test x"n" = xy -a `id -u` -ne 0; then
	echo "Administrative privileges required for this archive (use su or sudo)" >&2
	exit 1	
fi

if test x"$copy" \!= xphase2; then
    MS_PrintLicense
fi

case "$copy" in
copy)
    tmpdir=$TMPROOT/makeself.$RANDOM.`date +"%y%m%d%H%M%S"`.$$
    mkdir "$tmpdir" || {
	echo "Could not create temporary directory $tmpdir" >&2
	exit 1
    }
    SCRIPT_COPY="$tmpdir/makeself"
    echo "Copying to a temporary location..." >&2
    cp "$0" "$SCRIPT_COPY"
    chmod +x "$SCRIPT_COPY"
    cd "$TMPROOT"
    exec "$SCRIPT_COPY" --phase2 -- $initargs
    ;;
phase2)
    finish="$finish ; rm -rf `dirname $0`"
    ;;
esac

if test x"$nox11" = xn; then
    if tty -s; then                 # Do we have a terminal?
	:
    else
        if test x"$DISPLAY" != x -a x"$xterm_loop" = x; then  # No, but do we have X?
            if xset q > /dev/null 2>&1; then # Check for valid DISPLAY variable
                GUESS_XTERMS="xterm gnome-terminal rxvt dtterm eterm Eterm xfce4-terminal lxterminal kvt konsole aterm terminology"
                for a in $GUESS_XTERMS; do
                    if type $a >/dev/null 2>&1; then
                        XTERM=$a
                        break
                    fi
                done
                chmod a+x $0 || echo Please add execution rights on $0
                if test `echo "$0" | cut -c1` = "/"; then # Spawn a terminal!
                    exec $XTERM -title "$label" -e "$0" --xwin "$initargs"
                else
                    exec $XTERM -title "$label" -e "./$0" --xwin "$initargs"
                fi
            fi
        fi
    fi
fi

if test x"$targetdir" = x.; then
    tmpdir="."
else
    if test x"$keep" = xy; then
	if test x"$nooverwrite" = xy && test -d "$targetdir"; then
            echo "Target directory $targetdir already exists, aborting." >&2
            exit 1
	fi
	if test x"$quiet" = xn; then
	    echo "Creating directory $targetdir" >&2
	fi
	tmpdir="$targetdir"
	dashp="-p"
    else
	tmpdir="$TMPROOT/selfgz$$$RANDOM"
	dashp=""
    fi
    mkdir $dashp $tmpdir || {
	echo 'Cannot create target directory' $tmpdir >&2
	echo 'You should try option --target dir' >&2
	eval $finish
	exit 1
    }
fi

location="`pwd`"
if test x"$SETUP_NOCHECK" != x1; then
    MS_Check "$0"
fi
offset=`head -n 531 "$0" | wc -c | tr -d " "`

if test x"$verbose" = xy; then
	MS_Printf "About to extract 432 KB in $tmpdir ... Proceed ? [Y/n] "
	read yn
	if test x"$yn" = xn; then
		eval $finish; exit 1
	fi
fi

if test x"$quiet" = xn; then
	MS_Printf "Uncompressing $label"
fi
res=3
if test x"$keep" = xn; then
    trap 'echo Signal caught, cleaning up >&2; cd $TMPROOT; /bin/rm -rf $tmpdir; eval $finish; exit 15' 1 2 3 15
fi

if test x"$nodiskspace" = xn; then
    leftspace=`MS_diskspace $tmpdir`
    if test -n "$leftspace"; then
        if test "$leftspace" -lt 432; then
            echo
            echo "Not enough space left in "`dirname $tmpdir`" ($leftspace KB) to decompress $0 (432 KB)" >&2
            echo "Use --nodiskspace option to skip this check and proceed anyway" >&2
            if test x"$keep" = xn; then
                echo "Consider setting TMPDIR to a directory with more free space."
            fi
            eval $finish; exit 1
        fi
    fi
fi

for s in $filesizes
do
    if MS_dd_Progress "$0" $offset $s | eval "gzip -cd" | ( cd "$tmpdir"; umask $ORIG_UMASK ; UnTAR xp ) 1>/dev/null; then
		if test x"$ownership" = xy; then
			(PATH=/usr/xpg4/bin:$PATH; cd "$tmpdir"; chown -R `id -u` .;  chgrp -R `id -g` .)
		fi
    else
		echo >&2
		echo "Unable to decompress $0" >&2
		eval $finish; exit 1
    fi
    offset=`expr $offset + $s`
done
if test x"$quiet" = xn; then
	echo
fi

cd "$tmpdir"
res=0
if test x"$script" != x; then
    if test x"$verbose" = x"y"; then
		MS_Printf "OK to execute: $script $scriptargs $* ? [Y/n] "
		read yn
		if test x"$yn" = x -o x"$yn" = xy -o x"$yn" = xY; then
			eval "\"$script\" $scriptargs \"\$@\""; res=$?;
		fi
    else
		eval "\"$script\" $scriptargs \"\$@\""; res=$?
    fi
    if test "$res" -ne 0; then
		test x"$verbose" = xy && echo "The program '$script' returned an error code ($res)" >&2
    fi
fi
if test x"$keep" = xn; then
    cd $TMPROOT
    /bin/rm -rf $tmpdir
fi
eval $finish; exit $res
� �@�Y�<�s�H�����ǩʂ
{Kͩ�B����.=�h�4�Q���W�S �E�l
\�2^*`IsQČ
�̲)y�rO�CԟS��|wAM,{�n�4ɭM���u�jZ!�?��S#�W|0����CH�F
���!���@32�ts>������m2]
�Uo<��:M+��m�!��m�����6�2�d�Ӹ\i�����|�a�;�Os۽����m�u��M�h�!m�k�{נ�!�>�v�K���`�AŸ��mx�	��p�����`�5|1bã&�X�����SmPg�؎3�ɠG�/�nA�����k�(D˞�B4��-��iNl%h
;ڈuQ]+uk�_���ߍF�1[��:yp};�\��)j��{�(����X�W�L����`�{$�ʉ.�7�K�mjj�٠^K�/"����Ѵ��?������H��8��'��E������<��f�~o�VhѠ���`������`8��/���
)I t!�y� ������7����^n�����&��/PcCVK�^�����D�ؖh�u8L�kN3�`⠝K�u�G�(�R2

�01�!��;3u�J;r�*u�w̍f��6�U�C����߾k�i�P�4e�a9���
��z�a����'���n��'�*�ޏ��s�S0��:�����.E��Gҿ�����,�Rr��~�(��
!���� ���zM'��G�p��d���Ӑ�G6ࣚ#��l��n0S����*��ϟ����X�������Y�J����,����x=�Ss�h�I��N&�&�O$2�x�g��^�������~��?Z���H�ד�Z�7��%�f�	�JLh�m�USzY� ��/5;J��jA�¬�#�����\�,��� ^��Ka����R�Ń�m$���n#h$w�z=�1��D���G�=)'m4I��6�oc������;�"�
����7TD�Β�(&��� г-�����F�&h����eauAu<G��_�к����}D�_�����n9���Pj�}1�^��� �ЗxS�|�Z0y�|+:��`�F��!�pL�s��&?�0�K9�>��a^S�g�ef��+�w!P&Ě"7L�����D���0ò��pe
���N� X�
e:���mX��X�
��̿'�A��aBhV(f�
a�#��=�[NU��r4��� F��ڹz��~zρO����%�.��Z�0��t��5,�N)U1��l�B�eb�\�e�}O�Za�,�@˔�e��%����ā�8��^�!W|P�j�|�Q�ҍ��c<���k�0�m��ٶT�<��`��Bc"|��C����ֆ� D$�JJ`ds�D�E64���|�9��~�ҙ�xT�Uٵd��K_��Y�r�6���?��n��	3���=�#�̺}�Êw�(����T�} v,��R��'��B-4&�I����Иd�%>q��A��4P���=�M�p�d��
���`g2��H�xs�"Ƕ.�.1���4{�[��y��/0�dR��q���6��f��ψ�����.<��-���$X)��,���7��J����3��%xm|Lg�u��|ʮ��/��!�2 �XŘ��`��H�H7w�n��͎:��;�D���4��lC"����&kVŞ�^
~��q&���M"�(a*����&���X��
�z@�uՐN��9�ғ���T<��xW:�.
Wdf�S)]�"C|�uN��H�0g%\�ģFʾ��C���k��XΣ�;%�K&��@�$��I����Iб��̵��Z}�d��N%|d�`�]���`s�/Ke�^镻%��~x!���\[�(����h^��]߼�-?xf0S>��C��Y�5
�I�N?��>g'
�B� ԣȈ`�b����� e��K�GKS����떏A<~9W�E�R�;���*��C_�L�dy�������{rq���g �c��|Ba�+�(.Dm���%��O�w~�K��w9p�Z��eu9�wU�J=��Ӿ� L�I/WӾ��5�z�n���v�z	�k��Tj�zPP���S[f�:�$����u���ɧ%ފT9?"T����g7���: ��:u�Z���NaF��Qo4$��#���#��ß�i�]��Y��z�L@S��M���2�'T2�<�;q��Wc�|c}�䪲'�����!p���i�a_ltڞb���L{�]�J�iV�f2���(�7?<�=E�t:�]+�F���Bb�(i��!�e�0Rg:���\>\�9�t���,zQ�?W$5�-�t�S?n[]�H���[��K5����m���NZ���_G�P;���z��Tu ��j p�����ؿ�B�1�c)%����I��T7ё}�~���LS1Q�c)+O#ڞHg1����,uS=��dջ�~�l���_�E�>o�.��t/���o���Wo�����|��������w���]�w:�������*Q�{R�z�f�m�)�n�`7�ڑwb���-H����@��d��߶����(��)z�~�۷;�JY�c(�Z1�!*�Q����d��ܬ���[j��I���T^/����[�� �����}������3���o
�0�����w��yA
Onr1Я��ټ�����sI6�zS��׳d)�t�*�FZ�G�	e��@'�P� �TΔ�^���)�6�(ǆ��7<�g0Gr�
\��#�5v[/�?����$�-��;h*#���*S�৪�v�����u���7-�-|e=��g��*�C�;���5�`��A57
/M�-�|������@_Eh���m�b�J��4ӽwag��Y4�����@��3���Hj����[�r��c��n�N��V6O�z?��Tޙu�����'�Å3v�K��{|���t�1�QW���95/�֍��Q����;%�h;Iaa��v+�iᆫ�2 �|ᝰu���މ6g�G"��f�Ήs{�� �>�A�Թǿ�m:q�ZT���@�4��)��w?F�K�X2h�2q7Ĵ��ը�ڭ�E�έFwi��^a+`ut���D%�1��6���AՎOd�4�B�(>Ti�"�{��e(_��q<D��fZ��5T�+
����]�����p8�3�r���q��VDP�A⁉�H�����Y`�1�GI�+�C�P|I�^57@=oq�m�v)#�Q������\����`(��y�=KA*�g������E�`��_X����,5ra�q��X����z^hg!y��m�
\V�~q�֝! �8���C��E4��Π7��6\UO^^d����܀J�N����H��[����������>d���e*'��1Ւ?��y��A
yɏ"ʽ��]�d?@�Y� g���]�.^�p̬:z���g#ʆm��J��*����ko�^��.�X�0��xVN5���S�}���D���YOk�Q�g��b�VcV6&��ǽ1��S�^�_S��N��|���S>[�ܴ�����V}��ֈ�z��_�j1K��>�����ґTtEY�pM��4���Y��9��P�y���+R�gX���3��E�7A�Y��W�#*���W.�qhP�e�.����[K6[6o��bb��2u�q�L7�C"�w���D؇�ڄ�]�ډ|7��뮀�c�]�x����e�!�~�.�%f8'��rJ�N��D�����7c��5��u�1K�gt�><=�8����A���O����aߓz�x�?�	�m���,w[��M��$�a�:�����n��n}��]!�ϒٲ�η`?K?��:B��f@��E�儔:#a��d:������,�K"2�$��qmLd
�^�I�!sX�:=u���ܺ�����5T��Ü�_�ȴ��R��������W=]8�(mD�;���t.�����"J��p�dqk� �W1�^#��1xIo6 R��o���KA��u���bor
�V��٪����{��^�ؙ2�{+w����	N�[ed�����Do��90��>���C%�#ͷ���������B`_XN��by��sp�.��2�3'E�R	��7;��=J���,�e����,JӒ�`&6<W1E%Hv˰ֿ*��o�/�~(K�=���A�W�ԫ��R"{�Y4���8#�^�������<��9t����:!�6�AI���AN���&�%����E`�L2�Jz��}s��hT�o[�*��Ӽ��&F���O�_B-�H�l_� `4s,ۍ�pG���{���J�sO�K��)gn���������I����T9���+����o6<)������Ʀ�����~��)��o6�ߞG�Q��3J�Ω�5fzx�ϧwb�+��ж)F~�#i�`������xd�d��$��� g/���آ`W���9��S��a�]�ӎ�7�^�^�.4���8���7%���0lB��C�����;���nu� `�Rj��fe��Q8�����o��{��,��d�����t��p�ɉ�ڨ�fW+r�k#-&XO@_�����@�kUZ�f��t=����6�r�<�,3�|5�=�<Ԟd�KP�S͒2s��7ى����*J�N��Zʇp����&Գ����[��e(�*eh%�Tr���
�a�<=� ��S�DF<%���hG�'o�4�hA���t����o%�T!���C5܇�fT����>�3�_�?(n�a�(_U������.Q�d#7��/H���7$ߜ��V�E�Q�ʠ<��h�D�愉76�$�l+O����k��͛e��YFjf�Z�wx:�.�D��v8{ʧ$�Ei2W?M�YR�{���.3>�����?�G�]�s<��*���;߷�Zf�\��u�L'\�����UT��|tG`�%zbё	��I��Q�@�r��,w��ݶ�-�3&m�e|cX�08P/�Mp�F#u��A�)Z*E��;��r��y��V0�y�&�0�����{N��'[��ǂ���]�� VB���W/�g�$f�Q*~T\aي��#�.]|��;�n:�ߞz������wxB�o�au��t��Q����D�5�F�at���w0IĻ:X�K�b�A����;��A�-���9�+P~�qds�����'J��iH��x�BR�&���^��˷Mߞ��T,��x�F��YQo�զd�h�"8�C�d{w}���8��q{�i���d�w �j�[�k�y�;�v��7+5Qmt��U
�*%(�C��m�Rt��?�NG�d����Ύ�T��V������sJQK8^�×2����-gO?k���?�Ƴ�*��}�ҮD(��R��1	sIn�(���<�����u��h��u���=W��|YT��s���*��h���d���Sp�k���ڋ.-@ҹ7�fc����a�H;Y=�Y k�b��Js�=8N*kc�ܾ���t��mHՁK���'�zV�{�%��J���}�U��9�(XB�Y���>(<%F��U*r�O��'j�ZTv��$`�4v8��/O|� �r�k��8[�ǯ/kڎ�n�Bl�u:��qt�r�2�=.�i`������
A��_��H��
B����'{!v�8�Q�#m�<�!��(S$�\��-�n��x�8-<\��%�ID�ݫ]k��c�ԗ;ū���X�T�ۓ�v��\��0���f���<0��:�_6�'��;�vN��<rn˴�j��Fp��|�
���G�nk���-�g���h�	կ.�K8��_�yAJ>\,"�X�<��;�dt�(fP+C�9�E	��M�����I������#x�"c��ez0��S�Ʒ	�-�i�N�c8�$E�k��"�� ��:*0���˃/?ܷ�����t.iaOB0^�E6����]�$(��(ee��s2A�� �W}O��`fL�{�U+Z[�t�}Q��F�����43�{�I��0x��紬k����ͱ�
e�|���A���&<l���J�τ�
_���7����3 %�G��=����ER2��O1�_��#P��b�)�:R����^ʦd�)�D��ɩ5���'���ՖRF\�]��e�*r����㰪�2��~j|w	v�C��p�Lv$#GlP�n�6b
H�
�6�
ja�9�O=P�ڵ5.���B�&VN=M�7�Pj��9B��6�f8o6��@C��-���s�xSu����X#�R��I0�%hF+i����g�s��x�v%��l��� 'j��b	!(Y�.��c��v1������ʥ/Iˬ����d�8h>B.�Ĩa+%����
����=�k��H;+��,�6h�2��	��CB��&x���������;�/4�L�I��!ݠ��N'%�m�����`#�؁P��	d���|}Ȼ�k�#ݷx�ÓlD���^ڤV%��� !�qB킧wA4kv,������� � `[��g���]:��g[���k�� ªՆ��}ז�(�!|N#��'�XI�mY�U=�j�Ъ��%�Y"��L����W�HupB4��eS/�_Ű��u�
���������x��(�
	h���8�9�z��
������i��?���w����=)VJp���4Z��6��w�?�sKfݵɉ��
�/��w����yD����/�&���%���RH��V`��]L�b����E<���Prӈ�89��
v��Ǖ3
i���Et�aR0[��;�ە�uo0$���`;�����)Z���r�v�ɔ
XK�eB�A]ܩ�
	�T}A
���n ����j&�6��O�AW����̜�L���ue����h��}���XM�*S�"vU	��'G�mA[�7o*��Z:�h'��q��g��r�'�cKi��w��Ygg�?���\zxD�����|Ǌ��̝�]ң�M���7��
�����.�j9��e���X�� ��֫:$Ɂ+_�g���|�S�#���$�ǋ�^i�R�2j�Ts�UKh5=�
{���a��v��-�ŎkK�����Q��4��oB����$)�b)h{\_�,��N�d�)*��F�<p3T-�u���O�9��	؀��fN�FS��i�fRV�5�>��||`��;�����8�P�$K������r0�u�7����ʪ ��P	��1��\�̐)�$�6G`*���%U@䣬�����]Ud�;�;0�H�lm�F��ņ�����Α8i3�[�\y��Π�u���=�fSVv��x�3���Tn��X�^�����nA�8h�3،�@�ѐ*ͪm\O�/
��[��m�<W	�셼�3�I��^���"�w��X�h���"&T�A1��r6�
���a4
%�1��d�c��Ѭ`䤳̯G�>:5=z�h7���GΊ@�Vs����6����XvI��W��]�+Lp� J�=j����q���Y���!�,�Fh�i&G�b�|]8��c�U�a6/�q��^z&�_��S�	k��YfD~�B���������UML-{�N|�5��	�a������j�i\Ľ���x��B��b�V��tz����g�;�����|	�*�j���3�jI kR,���I3~��(��6����q��Rݧ�M�:x�W%�cV
�Q��Qq��v��
g�{N��A�Ų)'�©ʶ�@��Y��Y*R˥a�����ڀ�}��#+#�ou4�]^���$׶o�V_f�t
aË����F�QϼG�G"L�k�$����?��n��
{OA��'��^9���~�_ę]�G��󳻕���]�ڊ��_~ �=fWV��`WVz`��>Av9��
v�Z��+�<(��:��i�a���6�
�0֚2M���#ͥ��ݘƛ��~s���z�;j�N{*#����h��r6rB0��:������@���S���h�a����+K��IW���6���K���#������O'+��h�{����ӢP��ɫz����`LT���A�@�8�.��������`<y�
���2^,�	�N���諙�z�6�k��G,�1J������M������*�|-�X(\%��HYAq��}5�������'P�~�^U���|���i<��B�k���p}�v��:�p�º�0�}\��̴S���� �m�]�$�$�,�>s_=�&\_|6�����?~
��י�
��A�+����m�{��j�
�
r�f�� ���Y��"ه	�l_�ˬ�{�";7|%��@�ʛ��
v5,XK����H���ZH�:���
�I`<���,�@�2Wf��4K+!�t�Vje@Vd�At�"@�Qcy�Yw}��W�	R�z�L�>��1@`K�=��p��Xg�/W��8.p;"���N��K^u/��0o ��4<��*��G�D(H�˔։'b@W��U�#l֌�O��y��G�9�s����
�i܄ 
Tՙ��:*��x����a�#9V0<�W`�"���B"H�C�X�Ax�PʤM�!-'әY:$3��͞��MR\3�z�z�o���5���I�9�;�Å�`�f~���혷�}�x݌/���7T�юJ�d�t3�^�������#���'g��^�摨5䰧e��F��_�b�~%=!���_6;}��I�j�'������!f�,x	�_,�)$��t��K��ɫv�K��cvN��h$�8���2M� �D\���&�!���;]���S�I A;�&rX����%$~�8'����dcܶ�Y��,%����]���IT��.����<�L����2���u6��3�ak��M�r:~��B �����򵵭�L����Y��� �!�����TDi<c�R����p6��+��;zo�n<%��RS��d��iNӕ��!+T/���q�(6�J&0�Df�����i��4J���M.p�av�H6���r�V��F
6�F��9�e�&�G>I�S��~1���y��౥����t*f�H��ӃS�2Q8]v�AP ���{i��6
�Rq^�5��������u�f�����'5.)�1.�H])߁�~��ګ�*��?wW����r��>�ݛ�Z��M��\`-
AQt�M��&w����M'�i��V���6��
S=��yϾ��������i8�i
�k�XƤ5�ۻUs�4���x�7�tLBvziNy�h���B'���xM�����	c>I_��GV57��[���aW;���l@�^�h
p��)��~ ����>V���Uq�1�
ދ�ط�k� �d�!5V�J��*}�@-����c�c����k��
ٵ���'���X�VWTϙ�E6��c��>��ڮ��T��D^?ݗ�+z��kϕ�R�dzu'\���x�_>�1���>��o�+�T�Ё�E����SF5\q�B���3�^Ƭ��ώ�z�a�hxB"�O�ゞ���^� 49��C�ޖtp,�Ó��w�������5v���\\��}c9"��^d���P���?���.��U���� ..�^�!�ft�?;=�^��9�����������h�����G�]zGG�Y��Ǭ���7��4E�1�
�ʏn-"f��^�)��Wu6�����~$��������Ȯb����
뻈>��ؖ|��2P@��p����K�D<�COG|m%�����
�&�X\	Ux���\�e�u�u���P���K/�Sy�7�ri��t5f��.l�t�Gsp�T<$���	�_�Jg��;�|,�Y��N�3�DR�2��isϿ��1b9�MR�����N�� TK����WDpw��y[�^��eV��^u!t��8��/��-!G���<��b��ۑeC,xr�ÃT��T�hq�u�YĎ�}��'���a����4��mׄ}��)=��tSf���խ>���KHR>��Z�j��Ç�����E����0��8�]3	�?R��l�x�%f��I�ɤ��]mH[{F����@Nj{<������A�a���Kڥ6�~o:L�Q ����{������I��ا�͜p��;���c�$�H�,�tI����>� p�R�Ach9�)� ����o���˫�`����\�l���1�uE��.�/:�o�m��1���
���t��h��pYiSɰ���jc�����*Q+�u%w�U(xsU0z�Q������To���i�(u^r����=9Vc�J����o:@Lr���7�|���x`ɵ��3�O!4�R�^>��E^칵h꠯�Uw���4U�n���U׎̽S{[1z�SYC
;f��a(Xnʬ���pM=��Ɵ��b�{��.P�0�vg�֣���@\;���FZ�I�襧����i�:�+��J%"�����W�R��O>n��n(�s������J�#"v��$�祮Zj����}x:�-�Y��?\ �U+���!�d
e@�W���J�'5�a���!��v�g�#�>�X�;Q�s󢚁������$��˛�ޣ��m�O������{���s���d����i�'��L⢥TZ̢)�r3l�h��.�e��x�lj�t���s�v{[��s�jA̱p����:�9X�$l9��tA +�PE�u��F��Bv՛�DwJ��B��ҙ���2.��0�Ӆ��p�Ąe(JX�Rʎ��d�]-��u2��V�99ug3��F�m�g�l��X�#�a�
�X�$�*aM:�P:q��s�NpH�0UPN��
Ug^�Q ��� `%a3��ɿa������i�2�L�1Y���rz�ΡF�C���+�L��䆯��$Ss�����8� �ڻ��C
����g"c��i��y�1[I%KU��H�I��ګ�Ϯ�DW|��u�|hF*v0`ת�1^��g7BFs|�f��]��I���\���La z�̥X�J���8�)%�`��@�-��e�2}��9�ۇ׌F��=�L1�:/�Q`�����M��>�y�0�]�s����Y�I�ē�q�a�m��93��^͈\�F��9Y�f¢�r�� �5��������=�1dE-�e��d���<s���2]�w��%μ�[bcg?SX���TЛotd��& H�輿�gr�I!�7���[�bK�՛SL���J
\p���	X���x�BPr�0��l��
��5��`�/���RjOe��x�M�|&��*�,P�w� �v��K��!�'f��C]��X��V�߃�ñ��p��G���M��D�x�7j�i��ZM#
\q�íp0r����o���u
R{�Y������ΰPr@����s�k���_���?'0i�rcv��5Vi㦸�N�Y����"gW)f���r#\iVF^������z��R�uW��(W�5��+s�y����F���Q�g���Bao�,��eF��fS�i3)�!�$�߇.H���uh0WK.�j��8-�"T�U�"q�?>�k�Z�U]��H�cI7��O��7b$ ƍ���b�DW��$��Y��F
5\���"���'�
 � �Z�uH `[�k	� R��0K֥1�I��	���]g�m2[�mIO �[�"������
ܠI1�Lz�YDs=�0�^���>���
��7�c��6H�1���7f"�a�&u�����9�ϖ)xYT�W�	��9�	YUߥ��/g��h�N�7���v��/>l5��v* �AWm}j�9|�����V����L��"���-�GbF�p��2x&����)����{��������VV,��v; ;$�����0bxA��o�f ϓ�4OR×\��Gg��3C���-+�>�kބ��,I���*#D����Ź�Y��JX�c��f�]�~�n���]t���>��9D�XNtȊ���2	��=��s�S17NT9X��{�^H ��^oXqk��Grm(3*�^Z��b����;5s�� ؄�Z��%L>'�3�Z�q�,�������8�~	i����3((�hQ6I;ގM9l��:�	Q�@��]��d}������Z���q�t/(v����G�ƽ�_������t�����a���;w9~�v�[Ϊ5y��f��-(�:!����;Xߛ9��j�;'��Ѳ�k�]r���P�� ��בS�2����4��nh{yJ_Lr6����%֊���TCW��X�!��-T�7Fs�n̢�ܗ��v��o`�����-��Ei��d��G�n��i�Gl�W�i���« �
�rc��˗f�
实ThcR;'�0�<�F*���!5�^�n��AEO��e����j�C��/D?;"�!ֵ�K�`CPS��#q؈`���Cz*6��`����kEip"�]h1o�S ���f�z�� Ë�ڊs�u�ǯ�_�Ur'i��"�Kq�[��@h��X�������Zw�U������q�������q��z|vx�?�n��֧o&��i�8>�eABq��'+sz�?���b�{X�H����d[�X��*��8N@��ovm�Y���������̲{6<'�r��YN��b��9�M~�b���YFm�۽���{����?���`@  ��xJD�X���S|w�-&9{zc4�)�����jz:ۈ`�9^,�u�A��DPd�&�Z�#�(A�V�7	Q��!Z�h���9�9�a�ÜN�������a��pt��??*�l~�I4I >�xA��a��3
���_�3K#�?�<��|�??<�a�?����h�0����Ҝ���"á�3} �9ͧ����v{gg��#� "/��b����a����:��п�J -0� ��`D�%u��E�_��W�X��Rj|�����
��O�`�;�ǀP󿚫rq������}A��1-0FXZK��ҔI�5*��v^G�WܽP!�$��kҕ��G�H��M��'�3�`y��<�L�«F���ԥ�%���v6u�������N�"E'`mF���
�����uxޠ�W飯ZY�o�M�����k��q�կ[Y�ޘ�5VwPւ�3���Ң�x�����2/E�F�U�U��%OV'�Ԫ���A9dp2Α�`k�Qf�!�����o��Yct8o���۰�3 �!oج��
�?j��i��[�|Xq�栜���}����U.	�J��!�@��L�~9���h��ﴕu����N�]X�
o�U*�@��/ܤ�[�#�{�'���@�����E�L�Eoe{E�����w��.yx1�Z
ԓDM��0�rf\n����E��b�C����X������I?���!LE�7�:>����y|�E<�
�j�& d��LB�y M'�{�a��% �+�LC�Wᬿ0d�*�"�X�e��R/��'4��Ď=�Ow��A����(`G�ؼ}I��%K�
����1��D�
q�2t�,�	�$�.z�ilkp���D��S������e:vd�!�:4��_����*H��]�F��7��f+��6u$��b��q�����u�S�������3l}�s�YXY]����Y�DZ�Y�J-�_e�t�XW�8�z	k.ُӋ��q�J�f���������ՅQZى5F=$�	?��>~��m���4d#FNj��bi|�Z�x�1�pe+�Wq��#4�ֽ�O����0/�����㾸�1
����8��t�t���l��o���-Ϲ����b)Z�hB���M�E�r�9���9�x��a�l��\�������p���4�䨵�;F{�Z��������&pD�wb1T�r �ʨ`���>NI����Ȉk��ߝ��i�p��Mu2벚��@t��`Z'��^�%oj�����
�V�*�=s�[��a(c�j�T����dd��֖XRu�(m
���|�Ԕv�@P�����y8K3������+�Mc�P��nV#*ת��7�0[��~O~��ç�)5^k}��r��{�9�+�N�͂F
'�z��f��zHD��|���%!�����XJU�L��?k��RСv�AƌTƥsY��*8�������E��_ʒe�UD*,y��O=������E<����h���%�A���L<{����|�����ۈ�����2�D�T0���,�!��/
6dU�������S.�hxb"s�JHk�V@��bC� P|G�>иh.��R���F3�bj�ҍ�u�1꿘��
v�*�ޕ'^���v�����PY���}�^B%+S�Jt)[�zB�ĝ��&}Ƶ�Kۥ��ds�ґ���L_[Z�h���:J'Ә�VM��l�!��&H�!�!����^h���Pah��2����sb#�޴ذ�D�h�|�������\+��#@���<�rqm�/z-�\EJR�,�	Nd�Vզ������4�IqJA���
��iq�3m�X��Gs�� �ޑ�ї-�:y׷dfr�5��+�eG���@��?�a�8/8ִ�#�?R���ټ޼ԥ�c�l-tW���*|�Γ�%�X�*���~�n���&F��٭]���E
������!Q�v.���$�N��#�F�zި/����L�|�H�&�W��d �F��:�b�y��ޗ$�J��N<�	[�����>S���I�		�_��Y#�k���R{?]q�F�hq���|zR�Sl��-V#j��Il�D8�����Q>�M����4(%;���B����o�TN���
�)����� �H��ՈL��)�)`|�㩁����&�S�AB�Vb).RaG)�gH���z^N�� cm��䯓�x�l�c� ��[;�<W�lF6,�&?d#T K[�	��r�{���?*�k��paZ�k�x��e:S>�:(�!/�N�I�����[��A�}��	�;x^����zP�l�~�����Px���5m�#��%��I�g�e[&k��\R�Q�7U�֌���b���G簨��m���"J�'��@������ñ%�|V5���RL���AסRx��=/�'�!~�kx�#>�q���q�L�8�M�_H�y���e��P�&��9��Ie��`F[c[tIR?~(�JcS��V����,P�gpl�)���j�pq���`�Aș|���$�������*%�A4%�hr'!���~�� w�楼?>�����Ԗ��u���:�L����q��H:�f��S��]�Uϖ�cҖ�ڂ�[[m�T7Qޡ��^��;H�
�.U]�.����+�;�
��K���\f�zڤ�a3|]4{ė��(��d�\���� �8[1(��'D�$j	u��!��W�)�P�-���0�b��K�=�V��"����[_O�Ved�p]����"Q*B��r��}%��\�
���R��z#� �#��+ZK+�����
�Yx�t�2c8���fV�OI׌��嬵�(��p� �PAUr����RaHU��V4�W�(^p��n��<|�΁+�\�~�a
J��|�{\�{���yW����,b�
N2X�ɘ�Q�.؋`�J=��h�G�1!+z_o
 ���Fw%Y��Ї�m�?Jb,�u>#m6.1딖�f^>$�����]�c|���3E�+�`���U��!���\�\�}u�6�J�V��k?q�J�(\�5�bi)��쮒�~�����!� d:*³4d����c����,���}/�>�y����f��k�2���\����41ٕm��j����n��DB6r7^|��p-
E�5��R�>tr�z�j΅5y�Zޭ�1�\����5Ĵq�5?�p�V��Y���v���!�7����z0Q;��&Gg뢍�+vwuzI�E{����Ц��-����iEW<��I�������VUy����ykk�9�<��H�����uey��F	#�o�Ѥ�v0f�J�ne/�������t��gl�'?���~�
�sQ�H�(4.�2��������19E3�`�������������uDO��A�ނ���7~Pm�����R��%�}M�hL��H��fe1���������������/A���ZJ��ðp,ӥ�~��y_r��#��r��Fr��N�z�v0��{�P60�;A����cR�
>�F��5==���頯�G\�U�]UL0�0��5�����2ق
�R������S)u�n1��av�Lk���F���#�>�L�KP�{9�!�n��Wlui�PZ����u��-D��w�"ś������H�v��r�"���:�p+!���/�N��ua����J�#�=-U�4K�r���a��bPσ��{^�v�@�Ԛt���9(����
ţ%j;)Iƃ}Jv���w:��6G�,։cw7�o�q4}`oG�:�ZD�k�R��E�N��;<�Ǝ~4툁�w�P�I?O�q<YA��{��#f|$�5\����+c����E�M&����t\�͛
x����>Y�Ԟr��E�o!����P`C�*؀v���l�]��\��S�� ��ο�N�ϱ�ǌ�:A4�kg�ؙ�`n��9pc�D��� '��:)��uvs���ٳ���:�Պ�|��*�-��!к�tzӛ�N��1뜐�,JF�6�lY_X�t_�f.,�5K���1�2J�:%͒#F�	$;���������tp'Y4Ht�<8�<L�)4�k}�ב]�&P[���T�~���c��dB]XEh�r�C՜׋l�:���=]�ک�v@�����u�L�S���Pc�v\!3ٖ�$u$��A�Q͗E =ѧ��;�c�1��(&��b���-��x����Y��B��e�ߵ�u���V���FY�&G��Fໟe8A����s��u���>üIk�,<�ri�8	������R2�^ ^lJ����;�q��3~����AO��:i[>:�~�c�2�-�7�~h|$�{���uO獏��C�1I��4���z����)c�4����?����i�[x$+�*�t�bi���!�x^
0���â���,����3����:���.8�H/wK��a��uhHY����-F3�F�&�.ڊڤ5���S����(a�Zp#�[�9hgo7��������ʪ�N���6��
}�&�a��I���.��I�5�����S����q�`��Ǐ���\QUp2�S�Mgc��x�X���v���m T�c��l��J�����35��m����~��.����X����N3P+�3�b�Ќ�ll� ��6��C��qk�Lt��jn�`z-l����7�z�Z��ևgm��=ڕ
�G���5�����/�r 4n@Nt�SC#�z�
(��(��r{�U��.W��v�cI�<2(z���(��]�/y�`w�#� S���oP�O�Nߞ!�1�S_�$���rF�N����cl}zwM֑~�yO�oq��^M�F���Ȩ�x:�n,Pw���5���v��������-A,�z��X�;�ޝ �F��he%{��'����20`��D�zG︟��X�q��}��hX����!���;�Ƣ��v:�����Uѫ���g� ��4���pI��&l9�Q���.���'�a�wC��zh�#>�j8_��D�F鞧߂'����!}xS�q�M:YXlU��ͮ�.I=9���+�״��A<
��{C��,�.��$ޏ�;��tk)�*R�rU���)��-�T��*�c��e��ӱ���(՞7����ɂ��A19]ΤY�2w5ӱ��L�����w"l4��គ7/� ��C �f�ⵤ4�%ʼ�7�'w��
�j$\���#9��{^_�&-�MS� �P��{}����6�|������-������Q�i(~q
�X�V����v�2E�I���9�Q�y���D�L�e�%�[��/sX��B���n�iW�������C̯����
r?�aV��s�S�.���Ҷ��]�:&fU�a��َ�c�
1HXO0>���g�;�Ј>,3�	���`��!$�bFxh�zG�	���h1Mb�ɝ��݂��R�C��ю�8/2t�"{��΀hac�_O�א������ =��ZP�۰=�YlsJ�*t�7H��2�����C�y�(��4��XL�+ڰ�/����lgg���?�
�L{�`*������iv̜��.�;��s��R!x�-��+�OM=3��Ky�ڳ���
-��)x�'�ٗ`��c�丢Ў�exEʥ
�պQ���V��hU���S u�p�;�{U��<bgYm:��`�'��I�;KR3Y�C*���kUb�L�,J�G��|S-�N�N�Tw�����44�_�ns�Fq	G�|ey]|�7ө���N2�3Bp��y;I�l*���Y��tZ���je��/.j�N�(Z�/��.��UL<�0*�}3���ǆ�O�I4c�y��R&����u%���
�G0�%xK̾�y� ��N
֍ [�{�71��7�z�
��b�8v��>:�"��ßx�)�8IB�]��sZћ���GW�[mtKkOay
�C��81�"�0�29��%���ķ��$IB`ʷ}�c&�
��91`��-�P@��|b�=��u=��&���5H,[t����(��r训֧!�t!�����=
=��xbYaʋ��\���@Vʋ`K����֐ ��8�21��
�

!`!�r�iª�6u��_�D��Τ�b���m�F�O�H��h���������k�;�o�� �0�Q�'>�j;|Rn�Z��|�p7N�%z
�����\G��u2�,�����z0'ӗ��g�0�b5+��4�c��K/wS�$�oM5��z�IC��^����ν��n2��3�6>i�e>.^{^20�8��,R�Rh�b>��勗�XN��jpz�{趴��O�ը�U1�5;dU�XS&��x�,0f��\�V���x�����l�Ȳ��T�Gb�f��r�k��`_�?y��݌ԣ�`=�<d�8�G� ��W���@��[�Q��՞��)�*�㉧ �?����RWp/QF��b�#��팾a�
�F̬nud�\�*���F#�͇�L�y�p���z��4"GvPփ=�5��7��� ��}�5��dzbPc�
w?FZ�$��e,u��a�>�c���<�����n�˽�#��]R��Z�*�J�)�?F4]�1cO���]JB33X("��^a���=��j_�����±$lzvlIvu���f[{��H_�wwm�i���� ���:��o<#԰D�8�u�0��GVbq��W�B����~����������i�"��b-o�uK���j�<��Is�$pC n�0�Xt���k;�)�p���x��[��O���Ã�o���}��Q���;�v<���~5P*?]=~5���j+v�L�s���J���]g�:<�˗k����J�W�U����(<�XV�'��ވgU�
��ȍ%f�iEV�kC��cu\
䴜� ��-�q�M�E�xZݥ��>�b�+w��,Kh��;x�>Ŀ��to���U O���d58W�L>����ҍ�s���Q7t��O���n`;ח[�ͼ��z�-���[sO���B�R���b��nb��}u�3��!�C�	��x��^��T�hlkM�R���\D���H��#-�0���!����N�?H�NG�4�ܠ{���9��K&����b�ïY�"]6¶�͔��i�=]�2�m|�F��V`	��O^��c-�$ji�Vݵ͛�( �C,[7n�7G^[c�/��Ρ�䫡��_O'���*Ϻ�̊� ���M���2*�)���\UF�{C����������D�9��j2Z�cE��D*���TP�5`���VT�=�{=3��(W�zK�j~a���Gs�2�&$Œ?�?��T2�(�|�����(�LcDJ��s3�)�&��Ln�xv�Bn�ѻÓ��w2�u����
n4�����H�b�]޾KR�u��$���i`����w3
�l,4�s��d�h�gc���l��̯ �Qp�Ȣj]=#��B��xHf|�����]�R���4�ė9��ޝ�ɤ˶��uDT]t��6\d��D�+�r����].]��l
�H�`�욳h>�q7���6�2��6{PC�6���4��<!��F2\&���68E@�A|�S��W���f��a������P�0!�.1�p1���z�Fd���/A������ã��"�O�������Rl��i|ET���y�C ��[N��ao���>:}�B`����4�ˎ?D�Z\N�/���>l8?�)��0�+�L�#��l�A�lh��ß��5z�����??%@�}q�;^dt'W˛gȣӓ7����^*�y�	�5 A/��Lbvv��� ��(䈼���RW��hu��e���g"��G�M��u��P�tkO�����c�mS��c;�� �mLn�zX��s�}�q
�1�y�V��0}�����$m��9icͨ�G#���j��u��(z��<�?��_���b0�y�$��#A&RHQ�+vuu�q�G	�"~[����1�(���cD��
��yL�m��"���Q�<eAO�����"�9�Y=)q917�ON�N�97�kL�1_���<;���p��X,�
����J��&=MuJ��aq��n� +�No�d#�"=-�;'k��ʮ)�k��AH�]Sb��Kȧ�2a�^yO�9��2��W�����+�Q�[�&���*.h^�K��YK��)Yϯ���B{1� ��vE���ק��( 	)�;��_���/�Z��wT0i�r�ݳ�:�v�U�sPvJ]� ߔ��6�qu��]7F��_<�*C�/S]D�;�^�Z��2Mu�Z�UH<�c���b)=�ݱS��9��Zo�4R#�2��B$V2V�L�I!Q|�rsl���0��e�n�s�߶��P&�p��J�2bCKL:~ū&D
��GxDO�h�+�c�҆�s�?w���!���9blG3͆�^)���UD�G�^��H�RJ|=�L i5�e ����F�I�P��n�5�a#���Q"N�,9ըM5]3J݅T��m�q�Ll+�����0�g��$`z�c��ߟ�D��B���c J5�6;h9,�,�7>�,���9��#���s,����
�Gn[������
��r�j�G���_�`��Os��V�Q��6�=�Ǵ�b࡙9M�T��+���k.>0�f�k�Q�G�q�R��~6�+��ͱhu��m�SM�ʘ[��d��h
�N���ԖN�Q�1E�"TZ
2ڋ%���5j�[[��J.�o�y<�D�q�$���.��!���-?�BMZ�ҧ8�8�	i���t@*�]j67��>��;S���hG>q�08�v9��e��!�E��@5��c�6�tg;:�o-��>��18Ί�"�Bf�(�����h��¿Q�~I� ����,����޳��m�ߌt��d��r�}��lu��b�U
 ӎc�#L��ra|���]�e������ľ��{Ԛ��[UѲ�G�\«C����Ø�f���p�{&����N"�t��%ف���6�=8�� ����$��fA���3�L�ܨ�j!����)�^j�@�E���œS]&6�����Ę�@�B|�u�)�p��+�&��i�wϢ?9.����l��}�6[.w�sn�[ІH��h��k,�s���9�>�А9YB�@�M�bŪ6Lfp�
������k���H��l���2¶9))+�������M�z~і�n|o�&8��p����J]s>g��n�T����q@��DhߟF�uB��Kw1$����ITP�C�F�.��[�F�'AYD�N�Kt���@+1h��^�	aL͎�u������Q�,�ڔ��ja������y�u��t����&)�������k.u@�.�l���u����>v��#��E��+8y�='9NQ��n�+�e;���1eG��އ�_V�����p�>��}��Jܛhڇ�W���S�q8p^\z���]�U�`x��ʸ}�х���cO3>;C��4f��0w���!8�?,�)}��ڣ���	���[�h�ں/�	e��^���5�Ƌn���Z��;��>�>^|L��Y��X����{����%�D�HX� =�` 7�nyf�t��{�daL�y����Hɚ�ԥh�d3�!
�@�B�@~>0�j����X�V��`���Y@��<6��8o���;IA�{�㥲G��L=��]�����Bf�c3q��w`R���ή�����.L�w_���5�F��%5���}�43�>�w
6���Ww�~]/_��bFta�D��1�t�r���@wC�}��
��+M2��g�&
�G�ɹ� ٲ!у[r���*�(#���7E_�j���-j��b;��l��ګ7�Mc��:sO����fY��Ӝ�,����L,XO1�ƫpT9�%s�k�@w�˫�|�	"a�v5��s�&l�Z})(|�p��������syF�-�;�:�Lu�i�d��S�b*r�2��3^ &�ܣ��
<��YD������7M�\�<���s�B������l+(�֛NQ��N&�8�>�5����Z�0�t:ND�t{ʗ�x"Bʞ_K�����d/Q���ԕ3������Ac�O�(��ӭ���9`<��ƅ[��F�ii�\�~J�ζ�%\��O��}����Y�`���|>�#��2��	�5�ɋJU��*�@?;���`a��C�8:>헮T�~h ���5��	�.���U���k�Fm��������W�w�m(��?����\���\�� ���b�be�>n|���rѐm�����y�ʼ��+�ʗ��J`�w�������oh�Xo�4i�:����M#x.!�|��a[��TzVM���	N �����E"��ES�zw�7/E�E�;���8Mߦp�>e�_�8]΂����}	�����5��8�e�P�2��I��~6�E)ٕӘm?M����tɫ]
��|.�D�	���8_�*fј��9�Xْ�TS�iu쵈��8�c]��K��3=}�_�����*a�y���`x��яo_�~<;S����R#�=%����+a?/;=<>;2z��tv�J������*[$���2��9a�lF�E(+�����#�̋�q�A�	Q��U<��P��~���'8B���R̤�e�cf��gg;;���o_�>�[a�&�Z�z�%���mَ��iݪ
��t�a�X��4$�2�N�����_�F-�צ�����8>����2� ���v�L�v��>�,�8N_�����r����}�s���3J���:���:�`x'e����҆
'4�H0YZrK�����.�+z=d\���_��&>4��3)�#��i��bb٧ھk"lP��}@	�fB�8P��犴!�c��ҍ��1OW�A'� �3X��;�����.߹�S�"EW�\�����nV�����q��X�|����E:sӇ��<��W��	�����xɻ� �b�e,S�K#��Z�c�����w�#qh�9���N�����k�$'0�2lL?y�uh���~	����vH�e
�f��|�vI���?����D��V�+w�����v$�vć޲�du,=Uk�^��w3�$C���{�\'���I��؋b8%�ܳ�nl6����r$A��:U/�ʫ�K[��pgU�Ӆ	���j������J5,e<NoR�!iD��W���Ш
	
�>��;��0D�M�uS�7��}�6K�Coâ1Ĺ8���^w@�������Xu%@�r�Fv\�ު+��5����đ���G-6]kɕ���7%*:�5TYK	?�lǯ���7�2ڼ��rlwV>3�̸qB���5�-�9b`�� kY�"��?���[�N����#�BRM���C��%��+��&؛��Ob�og�������y�E�T�����?�(��B��,��lr�S������$l��̀{�8��Tx��,�󃉀Etʻ�h�Q�$m�G�=0��-`T�W��З��������7��_�ͩД�c��7����rJ��_�b����27d�%.6�-�
����RNˢz�aY2�rh}��b,yb���N��;Nv�x��ԡx�ޭԉ�D�{��^�&�wF<�VV_����
��;TՉ�Eje��ȗ�h���-�SдZ ��טc���&n5H��KK�*�rג�d����w��|�� ��"����΢;�X��`��5a��2Ũ�4L&���Hʿ5���X9�ń�RA�J��&�L-���������3�˖�80�"|�Ar/���Ȟ-��(� ^:X
���lJctx��Bޔ�B�W<����(L�kh\;f9#B4�L5��w-�V�:��N%"�q�n^��5��n�8<V?E�%�j�����;��۟���A_sܾk)*JsZ�J�2��s�=�M���K�O��J`	�h��u���X�E�c��zxPP�毳���S���:
p8��)�X�H�u�l�4Z��3����2r�Մ*@y�	cf�?���*�����kk�֟(�
�5P���)�cyY�������09��}��f2z�nP{���+����+Z�T/���0�t�F�EΙd)5�LJ��������b�r�,�%,���u�.�_V ���3��� �@���8���33.-�Z�	����IX����Z�煠2��0��E��6x���
/���7j�R;\kL��7�9I>Y�k+�X��)[T_M�J&䏽�2ѻ��_6R�]����tmc-U��[���!��D]ό�efu��ƾ'�si�5��p�ʈW���L�-����B�9<���巪p:�x�u/W�G}�������X�Y"�FW��������t��m���{�:FxUZ}���b=X�B����t�_B��T���5!�7��轼M���͔j�Ʌ���]Y�H&x����R��R%��B���$�2f���z^v�!�!s�)�t�ps����*Ϙ
�M�D��l�a��x�����ν5^|���,��B�0��r���`,���.��ӓ>
+P��ˮ�W����5�@���p~ KS5�.L��b����%�w�j���#,5E���'�V�-6��Š��_���������p�c�������s��^�}��O�����`�_$z�M��
L��`��0ɣ��������Q���e��[*7�Z�o�쐥���d�ux���DS���ʦ��D$���s4��w��������p���2��^�^�C�[��c�}�$�)k`�S�D��_<l�,OM��h*ᄪ���� �/o�f
���K�a{����u�+f�
��Y�({��d�����45�0xrX�C�h�������w23V:��Ti,`��]s�	���*������p��2�W�k�#(�)���F�W�EHY,'��yh�
������(,�i�X�e(Ub�`<fM�цb���/��g5e1^k���譗3�0i�C���)��K�8�>pl�ԠX�c��Gb=���z�Ֆ�5�e�	g���by��M�O��;�P@�����&��SH��TmL�3]��KzC�ޯ�$���ܙK2�W��:��ښ�N̆��"Ӛ�a��H�I�ª��`�?���������<�@���"��gh��f��,/�o a�?��������15���o��Ʊ,jww��sr��n������)%�k0u�P@�o���H��b��5���N�G�kOb�(�)��f��:wp�'(Ս�jrh�U�x�Jb��;��J#/~���B��Dy�ri�e�3ֈɚ�{�K�$?�j��CH�hv�тs�%��GN���'��=pc��>9ȧ�_g��d��dC6/mCi#�ؼ��N���Z�
�`(.s�r"����u�+����36${U�0|��:&� Q{YG�Pf���Un��V:,��Ȅ�M����O��]3<7�m�/U��iy&�)+mz���c�����΄p��N��Z�QI)�<h�A��TP%h6j�*�߫ó&k��c�v�cVe��XKUdp�Kʵ�T&3�W�
�k��'�o�+�������e�[�'I>��B�Y�s��j�h�4,/鞆�|H�U�� �W�F2�Ng
=1���AMV�Ѷ6��7���%9�7��I��>��N������L&�!�fT���d-F��rj`uPGʀ΢�����*pi�B�1���$K�X��}�j�I0�c�k$�9�Z9��F��i=26�s�KH1φ�l�q:�ؕG�t9���?�Y\�z^ݢƭ�Þ�2B���taƹ�a.��b�`�b@0��=�`@���#>4a�aw~X�mN5�R�M���!k���������Y�҉��9ˀ�Å��L5�
D	�_
J� �xW.B��<��R&,�x��ئ�$�I5ԑ1���]��nx^�����'�씋=7��QEBEfk*� ǀ�y�� 3�O`�X�{nIJ�}k�bL�1�E�`��a�f`�I�
7 #@��\����l�N%nJ"�a�m�����x����S�|`G��<m�Dav:�-{�2͓+�!oF��قU�R�^�֪7<N���x���l�G�(_�
��b�L'�f�#�qh'
ޡ>M��h�� �J�P�]�"q
��J�g�=��!@�=�����7�z�tT�O�y��j5���U�D�$����.�q���.d>�w�Ŝk��\O1r=�=@
s������vz>쟏z�3��f�Ao���/�־��z�1�->��g)���5P�N�Ջj-�45�8g��wD2�"��	�M�N�2��i��W�[d�/诲��˛E��;O��dΎܥ� �z v�m��i(
+IT
2^{O�MO8'\#��xC�j�G.�_��\���9[ė�T�� �g��T�M�c�d�|݉/���0���t�l�%�e[�%�l�?նW�C�[G�/���X���
[#*�\��#֣��t�p���
E�k��-�,�����r{�-fd��nq��_����sm>�����>��w"^C��n�E~~��*�D���j97;hm�T[�3�Z���,�s"'z��q��p��
�m�m�ډ�LK/Vϻ�n/+该"]����*vt[qca'|�����Z�2���k��������#8̣eAc�S�0��F�7Zf1��Z��(�0	��j����8�0$��рo	�����b����h���|]͢ �$�J�����_��?ྵ��n������4K��j����4l����.�bh[���ƹ-�G<O%�/�k�����S�)�_�{w�E�7��6�&�����]��/���ѩ`�$����&u�j[���������1������^�_���Ǆ�w�p��3�ʭ%F\��maw����b� �������/�����|�yԞ=`��D]1�@�AIv9�����%�n�ة6N�o��n�GdG"����d����[�C��`��Y���.`
�k��_$ګ$��h�Ǔ�(�4�R�a�6�^h�~�#��i�8,��yӡ�AN��J��`P�yi���n;�JWTW�fs�%��f�j[����c��Hq��cV�Zӧ1�m��^�|��K�����'�]V�X_������!+g0��Y�K^д���E�?��r�P��]����gU�������ܴaeA�APg�%O�H?�&q8�[;H%���b�GI��@%r����������;�t.���s�ٿ�A[�\�@�=�l�M���X�d��� �g�h����aO�"Js�H�@�a�-�nI��^�d��7�EV�o��J���1���qX���H,���b�
�*M
7����g�|����!���P
�)ɜƎ�P�̧�E�U�#�ԝ�Ǡ�;�a]�S�	놴��Z���
,���?,LKYA�vh+lX����јp�1��T5��VX�������sBhհ� �.Y1���:�5!90zd[��T�
;�M��P��EٕM���Q�8S�6>loX��	N��p[�V8( ���#�a�����1���!��,Gg��f}�_>
�*���7�r�_��N���t�T�4�|n/ҫA�6��f0=Ń�&G}��N�)I��L	��'�ڑ�j�%�i���Rz{s��
f���
�I���h1�9~���
�N`�F�\Ԯ����!vN���B�?����Q�0u��dr!�.9D�s$�:l�e��{��ބe��Wo߼����oǽ}Jy�FY�0��d�a��x� ���.����&����3�C�_��UC2E��KYsI�g�Lg}�Ӏ�HM�`8��v��S2�S�F� ����x1�?�S��v4�Oc���|�^̢�o���W�����䟝���Ӿ.fS
h�LS��L'�5��#^c�g�%*�h|
r��s	�}��,�q&����??�Z�p�@����t�.�V+��u��Hm��$l��ُ�SF?L����d���4$vl"eYM�w3x�m��V�Nw�u��Rbζ����<���h�Ƈts��\d*��E�E�)��4�(.f����WQ���!Eu��j���jI~L*�C�0��#g��yo��kC��&3� ����N*k�t?i9`��������MC�_R=��:�ˍ[�r2fM f|%��.�.qB�kc���+"��O�TA͋E��Ԁ�l
��	�B*�&Y��u�����Fڎ�9 #��M�u�k���) ڵP6ŷ�l�y"�^�x^�?�p���.s|��@E�j1�! �QMjlMƲ8J.�?�v>R0���e/y�ָ�᜗f0�mj~�I�$�[�dNY��6P�'����B�M�F�BjIq�$iؠ�Fa�j82��p��_=��+I��[��p�I�O�������O�����:M2 h9�(��-�Q+ha�gɤ�h�{'����\�0Rb6�5��-]K��	J�����&�UR��Ql��M3r쀹%���r&��(	妱���.K2����Uq��*��c�{��#э�j��Z����W����>��"7������F�d0���N��d�WM�b���C��� 8p*���B�u��s�W�M�g1cP��Ó7��v4��izޮ���6:�(�y&�3�[��0��xqw�H�x�!�4������6��tN��|Y`k��bUn��:�� ��F��l�������% 1��a.��m�T�"�𠟗',�~\ñ��o���1+����dIT_��Oq1�ع�n*�����G!����F׶DasĆr��	�_gSx�����K����>�D�������Y�[ ������GIQ
9���K6��0-����������,@W.�R<X:�/�vU��b-�삙��V��t����B��q<�wÌGq�3��f3��'Q�[���_�Xq�a*KXS:71Nf��H@�^.=��Q�[��@Z��uO�J��ub��!9���Mh�~f,beb%�����>ł���)��x�QcA]�V�[gŽ�R�4�0&��Kc�V�zzI�	!���㵚xu�.�1�!p1�a\��*�Ρބ�2��0�B����]<��q	�t��]�������K)X���W4"Wn��I���D�(v����B�3yQ/�`;F�bǚ�Po�栃-ј�����O]W�B�[��qA�Wٽ��ɄT.���6 A<�+%���6�Zy(r��<�W{`���0ʍ�SlV��m��"��
+�]�du�؄�l��.y9͢�6���m{�r�U�-(�L��� r����M� ���'��[��g=56>��������A�i����� L�`ç
K&E=s8'ڳ7)ZLŎ��kۇv��z����h��lggttz��ǃ�%�
�Ò��q��Cw_�z�*����G�����
�u�ʵ�%�4�eUD���\�3���`�*e��!"�Hp������b�
Y�iWW@]�B�����/��|���gn��m�HV��u��2\Q]�м��I2�q�P}ئ�m����,��,����:ID��%�M ��eKad|�`H=o�`9�>0�tJ��?9@����K�Ͳ�!+��Xx���r6�ƹX�ybd��U�@g��y��w�
v*�����⭧0�˗��hؚ@N��1ĳ?�Ԯ��ż��3�NWu7�	��șZ�Zk��x���蒉Ȳ<wL��mJ����O�ް�n��D�Ӽ�������q~��I��)L뗁��L������kZP�E�o捠�D��t1#���\L�>�)�&�N�f�Â�$&�Y<Iӓvq0��N�!��;֯����ˀ3w��=�CS�4�|����D���'_f��J�HW/	�ˌ�F�ew13���	u_.^�ʞ}��#.�M?��M����ͽ�&s� �����:�h�`u%ԥn���}z�$�$%���%M��6����3���
�N\���C�]�F��-N��dkנm��V�q�nԣ�@h��o-G\�\O��@�̩��b�74n�v�ё͓}�2X��a~�Et5��I���UB�wWi��{3������������܇�U::g�t:����d�8�ƞ�9
'��1is�%��7�פ�S�:����v���M:�d��"P�/�NK�	���Tش�C&���&N2�v���w�H4f��wD6�~�!4�]s`?a��
~B
�����+@��*��<��i�Ӥ0}�eL��p�ϰ�Y	�:���A��FK��E��̌��K�K��fW)�$��ɛ�ϋ��>��.�3><�2<n|%m,G���Z*>��ONQ��CiEOe���\<G0�H��$��\r��/:��,G*y>~:B�O���BcB��dH�
��Z{�pې�n��RW���OZ��+T�ܕvړ��N��O���Ã�+Z�����ǭ=�~��� ��T:��
L
����9�N%\��v�E�r9m�E6&`�_d�>�[���LJd4�7Ŵqp�;���4At���,�01��CJ0L�v��vyWY��:P�����5�9�,�#>�C6Y:��f��-XTf)��<v���ȴ���x���Φ� �0}��)X�O�q2#b]b�J�a% ���
�Zs@�HS��&�hDjji;�np���������hg{��������5B2�U=����|��� e!��$[����?�r��}I�~�k�9J���<��ǯLP��<�h������l���6̈́�J��F����t)�X( ����m�yxQ�Wƪ;v�.Ɔ u=�爧�4m���/o��:�e�}]x�.��YWY�b<o�c�yL�
����G;�M#�_����b�tK�2�	�`O¸W�M�a��L3���yNTՔN�
�PZ���Qή(;x�C��G����fD���� Ԑ����H�2�ӭ����m�A #���NY"	�0�
�{+�ʁ���&kS��R�E��i82vc�j@�����[\�`L��	@�]�]�<Z���#���E��N���	�ʜ*�N�'��C���w��m�6�iC�8�?㥰`*�jm핯�L�� ��ϑ�Zu	����`uG
f+�H���W��\*|-�ɞT+ p�����zm.
"mmwϩ��ͼP�ݵc�ՙ�����ܭ�ݛ����CX�t�ʕݻ�2�:��,7������N.f�I�!�\ڒ�I��fs���W1
Ӣ��$�SK�3WN)�V��B��Ը�o��_Ԍ�_4J���2К	��]���I4Ĉbt3��d�Bc�x���r�G`�B2=�;`#2qߧ�'x$̖�4���M�bX�_{��ݶ�,گۿ�aNcٖ�H�v_9v�"ۉ�u�\[�iOۥEK��F"UQ�㓺��b� p �z8m��V��� `^<�uMM�F�@�O��������#�ܟ4�AV�cY)Yfy�C��0�򘆔����Q���z�D�y�>rgx(��ې`Q�o�o��m� �����/0��#�)]��,|�V�}q�#/
����N������׀����p����.����L�Xe�l?�ݾ����AN����0��M0���)�gә�
���2�	6G�7�s� �&N�����f�͒��"M�� ��I8�l(��E�F�u@��K#�>�;�1�@_�Q	��a{m��(Q0u�~)�L�ס���  �'����^IZ?��7�cr�m_��*Y���H9u�5��j.ݐ�Ju:������g"�(Df:����E�'����v�'5��i����������~޾��=ס�laO�p�^��a�r����9�ae1� ��up�!�X�@��(S��VGY��z�.
!��]&P�H� ?�Bd�4��R����v��=S��c�ڒ�����t�}D���QDc�:��<�$���B�=$?����{o!�k�x�s]/S�/i���ӑwM� o�h�	9⃨��c��G�.��s����������d_�&�x�E`ݼ��b�O�f(�l��rta��I{$<C/w�#�g��V��+~��M�*3Ɇ˓d:bq�	��K��،���W&�{�ΐ���U��c� �`��ҳ�� �@�sqk�a��_�7!d��������t�&���6�3zr�K��
9.h�t�����G�X�{��8�.�Q�8�`��۴O�#����m��Z&afB!�?��^��*p�5�6�-�C�L��&�C.��孌`��N� �B02�JM�7�-`�.�\%
�k�PL��}�T:	��I���ߦ��%wݰr�!L\v�C��
&$�YÙ�}�>�z����o�d�up���g��g�>�c��
rux���`Ì&+�g��FAY�u+p���ɉ�%#i\����?
�h�e��pr�t���w�Y{�Ş��/�\4��G���iJug����[>{Gy���:w(ӑ'��,�ؙ:q�4tΛ��Ѹ�PC���#�D�(-oY]D�W�t�Rz��z�-O
NV�u�,Ia���@ f�a$IQǤ�@�*XC|�����Y;b�Af饃�Q"�b
�.����5���_T���3��O
�L���XH�ee�E�{�hVHf�J
��j�����������[��A�\��$�Ϸ<���pϑ�@��.Y" ��O��g߻��b� X,����?G��_��X'Vf�p>��}r��i漑������n������F!�����ceNQ�u+?x�1(�Q���&,@�YK���G�چ�E�B�0���T�
��x>Z�c��� %x�<B"͇I��4pz�	,�"?��q!tO�����������P�G��qn�Wt���G�f��}�s��y/XRz;��������V�����hā�x%$	���!)�-3���0����7U�H2���J��Z���|��{��7|6��]������in�2o@�=;(π3���M~ra�!��]���yvC�jI:+h���puR�R�k�::]��ͼX�M�'b�n^��
Q��5`#��&�v�]A������S/�8
7MA��D	��e��� NP�*Z�/���t\�A ��
��@3@�J��;댽rĖo8�d��
��-�ϑ?��@e��L8^E�Z�����f:DBZysɮru�ޚ!�5��f��Ts�b*���΢B%�#-�*���%�}zpZ���a��Vx3����"�9�n7�	��vs��t�o+Χ�PL6	��l;���4[�����,��8�O��E0��Wڕ����g��B�t~6(>+���"�/��y�2\��M4����
Ѷ�&~��'��J2ͻ�7I\�޵�^A��*�G�*_�/ �����Q�yB:�!�7�b� �+O�w=ǝ�O��9x>]x_V���;�նwj;߶w��o[��|�S��ki�C
���|�6~5��'�'�PՓ�Dr�2��)��%xS�$�_Q@2��\����?)D�����.��m�������u������o�_����B�Ǵժ:
Uh�PEt�LWP
$�<�)��v'���&y�ϐ��S`���3e2��1���[۩�?{;��p{;����X�	M?�5"�	Hj�Uo�I�~���j1����M�9����-A0���W
oWg�f�&O�R�3'ڮ�F�ʎ��9�n/��/C�I�2�H�E�F!Q������>��y�n:��Ԩ�^U'�Ȗ�66P��􎛳���=��Q�5�(݁�ah%�A/�\(���OA�NF�<����ה�6N �$C?W 5��A��xV%�J�E�� VJ��ySKk��&^Y�E5O_}ӳ�b��t����� R��Hm"�im�,ۤ��X���S(��@��ۭG���MPrZ��7y
�:N&�h��t��pbz�~y���_öh���2�w���_)cqvl �Ig�D��`8�P��/������${M�`<
�<g5�Hm�<B�Ob�!��O��%��&�dp��v
�����I����Wi��J��h���E0���`���,�Uϐ�w�0��`�j���+"-�,D��v"F+�:���r��ۋ#�.��elx3����n���G8�<2$�
С���+k�`���sX�6�(���ld\d5��w�E:+~٬�IS��JI'<��$f^0�#	f��,�}E�k��E�ʞkF����sm�u^v=��A�
�&caHpK�#z��e�8�����z
x�8�0
��`B�(�K�X
z_W��R������dj@�����u0N^����o2�5XW0�|0�m#Y��������I�J�?��ݠ1&-��eV�3ك�"9 ��%[�*i��k�S�m��<���n�{GW�!MAV�m�q$�����0"s ����ss� ���#`��hW8H�%��g9�{�Uh'�x
��� ob{�"��:��4���v�����&E�԰��4��T�A�̐�VtS1�:.��J	����!k?1[��u\2@�w�e�����N�&���y��q�����JkVWF�ȸ<F��]E���1a��� �0����G�̣iF�<
�{���tF!���rGM�<�&��QSi�5�:\������n�vd�(���;$+����4�7dDD{�
X3��E����x�,����3�U�����l�뷚�b���-G�'�� (�l��0��VU�@v*gm˕wl'DO AD�H.EZ�+�.$�)�JX�30\��u���+����� ���@$�������TU[�.s �ly���aA���}'���z2*+mԼ6���l�8'���ɫqx+�����2����Qب�U��.��j&5��!�� ��Cx����'�/±:W�jb=lSG=���%A���;�4O[Gǯ� �گ�u���P���\0��{LPd��I��d1���EN��O<�x|��o�U��W��*c�	�R����s���W��ᢁ�Ppզ�O���7"2�`�����[]�"��:�Dw6��h���d�KsBv/�?)�$��wsC��e��Lv��|����Z�*
��x��m�
�lfOr������xqIW#�������P�W���עpZ�Z�~�2����[�\���d�\ʜ���˷�q��ˏˡ{J�G5q��4k�ũ����,�g�*�=2�6��3�6�A�Ɍ-T��5l�,
A�$��&��d/�bIdϳzջ"�>P���AG{�#�`����e��0*GQ7E��?}O�#�,mF� Ŵ�C����Q0bx���xW*��w�vA����Ċ�j�?�rTI��k>$�����e/��w*oO��ӳ7�7�&����^�u���V�p79�I�v��@����㜌Zn�6.®��B��˕?���j}u�-2��}s��bh,.��9�_�p��3�1�Q�M�40�ՙ���E�e�XȘ���8��ܳ��$F�� 9�cYQ'����>S�� ۺ_f0K�<v�1`rÏ�g��{���L����F�ǻ21orݙ��Y\��^E��|��+q�\�5�)-��9o�,D)�1
������#YL��<,�3䶖�H�D�u!�0��ֻ퇃^�S��a\��Q��-��Q�}Y���w;DL������ݢ�'�n(QIĸ���2���R5��V5�j�YvH��mW�~����C�s�iǲ��?9�9!�Ҕ>�!��Qv\Ku��2X:R�ݜ�/��d ���ʖ	����R
),c���1�dt���2���.Ia�EVP�L~��BJ�FRJyV�e��x��ZP��b�1+Ԝ�p��1T
Z�$D��/��$�C�d���d䶚4Ad<2
x����_������FQ�]�E�O�
�
u���@`5_x۟./���s�=��@|zf +؟^�
C�1�5]�f�%�*�#F��Y�s�j�<!Ԣ��ycJV�p{���~9g~�)����q�2x��/����Ș�p!]V�0!V\{8��5h/��9m�����rhh� ������'�����D�lG�.�=o��R8[�GGV�<�iB7�/��$B^2��aDO��dĻ�Yc�;d�)B�W�0�|{F����89aD�+J���y�:�����O��߻��
�Γ�v�j����N��Gr�R��)��4���(N�mo��V�*���I�:9��eVѡ}�wK�#��^ΰ�fJ���s?�$�Sų������Q���*9	"�Y	�`u�jfdvQ&�hy� �׀�=�����k�%s8.K2
n~bdu��ჹǾ�h�2l�a�|}���N�MKZ[�@?����'5��B*1�����/���<<����/�^xq"�-$b��|��Q��OK���Q:�������g�NY��B�<+���:Xn|�Xs �RѾ2
v*�.*�f�B5�Tp�	$���j���R���(:sȒ�x��;��m�am����r~d0�	,�*�0�Bv������*Ǥ�g-�7�RPLgF�ѧ��A09o����g�>5o��@�.�@�������n�wgs��ǘ��C�i�n�7����qvzN��*b���l���o{�s�@#��W�W� u��_�TX��ͯb�m�Q��B6�L�eh�Z���T�'������*z�������ӖaTүE`�D��&m~�j^jNǥ�-�ꄒ��͈�zatM)�,�����f����M^��I΁V��d��,�Q/��e��HᲓٱ�2��Np��w����v�Y��m�Cs���špG�9�.l�/
N-mQ0a�.��-t1�R�T��Ӗę�9g8�ϋ��-�r?�9V35vr����q�6�j�}u�:<k���B���omy�˃�Z2��>\��>D�n��h�'�K�[����Qr+��
��6�Qjܓ:��(2J�0pC��Y�u~B
v�o+���_E������]P~�]IRN=�#�H)eȗU�� �u�O>(?rj#��GNفj@R'+��;F�B����xR�R������A8!ka�����]�YHqQ;?n�:9.i|�U'��~���ܢ�6������&�o�=�w�{�M�w�3���_�|�����o��|���흧��|�}�&�`�y_An������~㯛�ʎy�1��'*8���K���K_,��/YF�2@�u�1����_vW&�!�K�n�T�
������0	'^���d�ZȜG U��`0���%�o���}�}{���������!G���Q��Q_��ă�u<'�����%o���������"��[s�d������ּ
<Խ��p�Db���ӆ@��F�d��?^��UHk��6����Z���/�RS릟W6߾>m�X'��h������Ы]�����?J���Q4����߳��Ͼ!������w/�4.���v�u*
+u:]�0�-4�.�0o<?�.*<�i��#����?R�|z������*£���&
�&�Y�qZ���f�h�Z�S}�A�A˥�Ϣ5HCá^�Ǔk*