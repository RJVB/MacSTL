#!/bin/sh

# runDoxygen.sh
#


#  Build the doxygen documentation for the project and load the docset into Xcode.

#  Use the following to adjust the value of the $DOXYGEN_PATH User-Defined Setting:
#    Binary install location: /Applications/Productivity/Doxygen.app/Contents/Resources/doxygen
#    Source build install location: /usr/local/bin/doxygen

#  If the config file doesn't exist, run 'doxygen -g $SOURCE_ROOT/doxygen.config' to 
#   a get default file.

if [ "${DOXYGEN_PATH}" = "" ] ;then
	DOXYGEN_PATH="/usr/local/bin/doxygen"
fi

if ! [ -f ${PROJECT_DIR}/../doxygen.config ] 
then 
  echo doxygen config file does not exist
  $DOXYGEN_PATH -g ${PROJECT_DIR}/../doxygen.config
fi

TEMPCONFFILE="$TEMP_DIR/doxygen.config"

#  Append the proper input/output directories and docset info to the config file.
#  This works even though values are assigned higher up in the file. Easier than sed.

cp ${PROJECT_DIR}/../doxygen.config "${TEMPCONFFILE}"

echo "INPUT = ${PROJECT_DIR}/../macstl" >> "${TEMPCONFFILE}"

OUTPUT_DIRECTORY="${PROJECT_DIR}/../MacSTL.docset"
echo "OUTPUT_DIRECTORY = $OUTPUT_DIRECTORY" >> "${TEMPCONFFILE}"

echo "GENERATE_DOCSET        = YES" >> "${TEMPCONFFILE}"

# add the standard compiler tags to the defined tokens:
echo "PREDEFINED += __APPLE_CC__ __GNUC__ __MACH__" >> "${TEMPCONFFILE}"

#  Run doxygen on the updated config file.
#  Note: doxygen creates a Makefile that does most of the heavy lifting.

$DOXYGEN_PATH "${TEMPCONFFILE}"

#  make will invoke docsetutil. Take a look at the Makefile to see how this is done.

make -C $OUTPUT_DIRECTORY/html install

#  Construct a temporary applescript file to tell Xcode to load a docset.

rm -f "$TEMP_DIR/loadDocSet.scpt"

echo "tell application \"Xcode\"" >> "$TEMP_DIR/loadDocSet.scpt"
echo "load documentation set with path \"/Users/$USER/Library/Developer/Shared/Documentation/DocSets/\"" >> "$TEMP_DIR/loadDocSet.scpt"
echo "end tell" >> "$TEMP_DIR/loadDocSet.scpt"

#  Run the load-docset applescript command.

osascript "$TEMP_DIR/loadDocSet.scpt"

exit 0
