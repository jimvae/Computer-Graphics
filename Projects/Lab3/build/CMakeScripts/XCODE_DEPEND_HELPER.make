# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.Lab3.Debug:
/Users/jimvincent/Desktop/CS3241/Lab/Lab3_todo/Lab3:
	/bin/rm -f /Users/jimvincent/Desktop/CS3241/Lab/Lab3_todo/Lab3


PostBuild.Lab3.Release:
/Users/jimvincent/Desktop/CS3241/Lab/Lab3_todo/Lab3:
	/bin/rm -f /Users/jimvincent/Desktop/CS3241/Lab/Lab3_todo/Lab3


PostBuild.Lab3.MinSizeRel:
/Users/jimvincent/Desktop/CS3241/Lab/Lab3_todo/Lab3:
	/bin/rm -f /Users/jimvincent/Desktop/CS3241/Lab/Lab3_todo/Lab3


PostBuild.Lab3.RelWithDebInfo:
/Users/jimvincent/Desktop/CS3241/Lab/Lab3_todo/Lab3:
	/bin/rm -f /Users/jimvincent/Desktop/CS3241/Lab/Lab3_todo/Lab3




# For each target create a dummy ruleso the target does not have to exist
