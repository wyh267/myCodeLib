#/bin/sh


buildTarget()
{
	echo "now in " $1 " , building " $1 " Now"
	echo
	cd $1
	make clean
	make
	echo
	echo "Buid Over"
	cd ..
}

cleanTarget()
{
	echo "now in " $1 " , Remove All obj files in " $1 " Now"
	echo
	cd $1
	make clean 
	echo
	echo "Clean Over"
	cd ..
}


buildAllTargets()
{
	for module in $modules;do	
		buildTarget $module
	done
}


cleanAllTargets()
{
	for module in $modules;do	
		cleanTarget $module
	done
}


echo 
echo
echo
echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
echo "@"
echo "@ Wu's Code Lib Build System "
echo "@"
echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
echo 
echo
echo


modules="Tools ThreadLib NetLib"



if [ $# -lt 1 ]; then

	echo " type --help to show help massage "
	echo
	echo

fi


cd ../Src/


case $1 in 
	"--help") 
	echo "Help Information:"
	echo "all               build all target"
	echo "alltest           build all target and application for test"
	echo "thread / t        build thread target and application for test"
	echo "threadclean / tc  clean thread target and application"
	echo "clean             clean all targets and application"
	;;
	"-h")
	echo "Help Information:"
	echo "all               build all target"
	echo "alltest           build all target and application for test"
	echo "thread / t        build thread target and application for test"
	echo "threadclean / tc  clean thread target and application"
	echo "clean             clean all targets and application"
	;;
	
	"all")
	buildAllTargets
	;;
	
	"thread") 
	buildTarget "ThreadLib"
	;;
	"t")
	buildTarget "ThreadLib"
	;;
	
	"threadclean") 
	cleanTarget "ThreadLib"
	;;
	"tc") 
	cleanTarget "ThreadLib"
	;;
	"threadc")
	cleanTarget "ThreadLib"
	;;
	
	"clean")
	cleanAllTargets
	;;
	
esac







