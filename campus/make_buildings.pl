#!/usr/bin/perl

#$CC = "cl";
#$CFLAGS = "-I. -w -LD";
#$EXTS = "*.obj *.exp *.lib";
#$RM = "del";
$CC = "gcc";
$CFLAGS = "-I. -w -shared -fPIC";
$EXTS = "*.o";
$RM = "rm";

chdir "buildings";


if($ARGV[0] eq "clean")
{
	system "$RM $EXTS *.bldg";
	exit;
}

if(@ARGV)
{
	@sources = @ARGV;
}
else
{
	opendir DIR, ".";
	@sources = sort grep { /\.c/ and !/building/ } readdir DIR;
	closedir DIR;
}
for(@sources)
{
	s/\.c//;
	system "$CC $CFLAGS -o $_.bldg $_.c building.c" 
		if(-M "$_.bldg" > -M "$_.c") 
			or (-M "$_.bldg" > -M "building.h")
			or (-M "$_.bldg" > -M "building.c")
			or (not -e "$_.bldg");
}


