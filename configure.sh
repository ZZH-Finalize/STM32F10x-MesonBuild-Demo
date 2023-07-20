
project_name=$1
cross_file=$2

if [ -z $project_name ]; then
    echo "Please input a project name (or press enter and just use "demo" as your project name)"
    read project_name
    if [ -z $project_name ]; then
        project_name="demo"
    fi
fi

if [ ! -s $cross_file ] || [ -z $cross_file ]; then
    echo "Please input a crossfile (all crossfiles are in the cross_files dir)"
    read cross_file
    if [ ! -s $cross_file ] || [ -z $cross_file ]; then
        echo "Invalid crossfile path: " $cross_file
        exit -1
    fi
fi

echo project_name: $project_name
echo cross_file: $cross_file

sed -i "1c project('$project_name', 'c'," meson.build
meson setup builddir --cross-file cross_files/stm32f10x.ini --cross-file $cross_file
cp builddir/*.code-workspace .
echo "configure done." `ls *.code-workspace` "is your vscode project file"
