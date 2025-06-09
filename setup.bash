export PROJECT_HOME_PATH=$(cd $(dirname "${BASH_SOURCE[0]}") && pwd -P)
alias fault_handler="(ERRCODE=\$? && echo \"[ERROR][\"\$(print_backtrace)\"\$LINENO] problem occur, error code: \$ERRCODE \" && return \$ERRCODE) || return \$ERRCODE"

# print bash function backtrace
function print_functions() {
    echo ""
    echo "Avaliable functions:"
    grep "^function" "$(cd $(dirname "${BASH_SOURCE[1]}") && pwd -P)"/"$(basename ${BASH_SOURCE[1]})" | sed 's/function /  /' | sed 's/() {//'
    echo ""
}

print_functions

function reconfigure() {
	rm -rf $PROJECT_HOME_PATH/build || fault_handler
	mkdir $PROJECT_HOME_PATH/build || fault_handler
	cd $PROJECT_HOME_PATH/build || fault_handler
	cmake .. $@ || fault_handler
	cd $PROJECT_HOME_PATH || fault_handler
}

function rebuild() {
	echo "******************* Cleaning Project... *********************"
	reconfigure $@ || fault_handler
	build || fault_handler
	cd $PROJECT_HOME_PATH || fault_handler
}

function build() {
	echo "******************* Building Project... *********************"
	cd $PROJECT_HOME_PATH/build || fault_handler
	cmake --build . -j$(($(nproc) / 2)) $@ || fault_handler
	cd $PROJECT_HOME_PATH || fault_handler
}


function run_tests() {
    cd $PROJECT_HOME_PATH/build
    ctest --verbose
}

function generate_upel_artifact() {
    cd $PROJECT_HOME_PATH
    echo "Generating UPEL artifact for classes: $1"

    export_path=$PROJECT_HOME_PATH/Export/$1
    if [ -d $export_path ]; then
        rm -rf $export_path
    fi
    mkdir -p $export_path

    local TO_EXPORT_LIST=()
    TO_EXPORT_LIST+=("$1")
    TO_EXPORT_LIST+=(".vscode")
    TO_EXPORT_LIST+=("googletest")
    TO_EXPORT_LIST+=(".clang-format")
    TO_EXPORT_LIST+=(".clang-tidy")
    TO_EXPORT_LIST+=(".clangd")
    TO_EXPORT_LIST+=(".devcontainer.json")
    TO_EXPORT_LIST+=("Dockerfile")
    TO_EXPORT_LIST+=("CMakeLists.txt")
    TO_EXPORT_LIST+=("ENV_SETUP.md")
    TO_EXPORT_LIST+=("helpers.cmake")
    TO_EXPORT_LIST+=("NamingConvention.cpp")
    TO_EXPORT_LIST+=("README.md")
    TO_EXPORT_LIST+=("setup.bash")

    for TO_EXPORT in ${TO_EXPORT_LIST[*]}; do
        cp -r "${TO_EXPORT}" $export_path
    done

    cd $export_path
    awk '!/^#.*/' CMakeLists.txt | awk '!/^add_lab_exercises.*/' | uniq >TmpCMakeLists.txt
    echo "add_lab_exercises($1)" >>TmpCMakeLists.txt
    rm -rf CMakeLists.txt
    mv TmpCMakeLists.txt CMakeLists.txt
    python3 $PROJECT_HOME_PATH/Scripts/remove_solutions.py -p $export_path/$1
    zip -r -q ../"$1".zip .
    cd ..
    rm -rf $1
    cd $PROJECT_HOME_PATH
}

function gen_pdf_docs() {
    pandoc -V geometry:margin=1in ENV_SETUP.md -o EnvironmentSetup.pdf
    pandoc -V geometry:margin=1in README.md -o ProgrammingLanguagesII.pdf
}

function unpack_results() {
    local current_path=$(pwd)

    local dir_path
    if [ "$#" == 1 ]; then
        dir_path="$1"
    else
        dir_path=$(pwd)
    fi

    cd "${dir_path}" || return 1
    find . -depth -name "* *" | while IFS= read -r item; do mv "$item" "${item// /_}"; done
    for fullfile in $(find . -name "*.zip" -type f); do
        if [ -f "${dir_path}/${fullfile}" ]; then
            dirname=$(dirname -- "$fullfile")
            dirname="${dir_path}${dirname:1}"
            filename=$(basename -- "$fullfile")
            extension="${filename##*.}"
            filename="${filename%.*}"

            input="${dirname}/${filename}.${extension}"
            output="${dirname}/${filename}"

            echo "Input: $input"
            if [ ! -d "$output" ]; then
                echo "Output: $output"
                cd $dirname
                unzip "$filename.$extension" -d "$filename"
            fi
            echo "--------------------------------------------------------------------------------------------------------"

        fi

    done

    cd "${current_path}" || return 1
}

function format() {
    rm -rf $PROJECT_HOME_PATH/build
    for file in $(find /$PROJECT_HOME_PATH -name '*'); do
        echo "Formating: ${file}"
        [[ $file =~ .*CMakeLists.txt$ || $file =~ .*\(\s*cmake\s*\)$ ]] && cmake-format -i $file
        [[ $file =~ .*\.(h|hpp|c|cc|cpp)$ ]] && clang-format -style=file -i $file
        [[ $file =~ .*\.(md|json|yml|yaml)$ ]] && prettier --log-level silent --write $file
    done
    echo "******************* Formatting done.    *******************"
}
