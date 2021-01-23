# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.Lab2.Debug:
/Users/jimvincent/Desktop/CS3241/Lab/Lab2_todo/Lab2:
	/bin/rm -f /Users/jimvincent/Desktop/CS3241/Lab/Lab2_todo/Lab2


PostBuild.Lab2.Release:
/Users/jimvincent/Desktop/CS3241/Lab/Lab2_todo/Lab2:
	/bin/rm -f /Users/jimvincent/Desktop/CS3241/Lab/Lab2_todo/Lab2


PostBuild.Lab2.MinSizeRel:
/Users/jimvincent/Desktop/CS3241/Lab/Lab2_todo/Lab2:
	/bin/rm -f /Users/jimvincent/Desktop/CS3241/Lab/Lab2_todo/Lab2


PostBuild.Lab2.RelWithDebInfo:
/Users/jimvincent/Desktop/CS3241/Lab/Lab2_todo/Lab2:
	/bin/rm -f /Users/jimvincent/Desktop/CS3241/Lab/Lab2_todo/Lab2




# For each target create a dummy ruleso the target does not have to exist
