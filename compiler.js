const { log } = require("console")
const fs = require("fs")
const path = require("path")

const inputfilePath = "code/index.@"
const outputfilePath = "out/index.cpp"

const data = fs.readFileSync(inputfilePath, "utf-8").split("\r").join("")//.split("\t").join(" ")
const std = fs.readFileSync("src/std.cpp", "utf-8")

fs.writeFileSync(outputfilePath, std + parseCode(data, inputfilePath), "utf-8")

function parseCode(data = "", pathName = "") {
    //get the lines
    const lines = data.split("\n")
    //parse the code
    const code = lines.map(line => {
        //delete the outcomment part
        if (line.includes("//"))
            line = line.split("//")[0];
        //check if the line don is special code
        if (!line.includes("@")) return line

        //replace the no syntax tokens
        var line = line.split("@").map((part, i) => {
            if (i == 0)
                return part.split(" ").join("").split("\t").join("")
            else return part;
        }).join("@")

        //parse the line
        var [func, param1, param2, param3] = line.split(" ")
        //identify the function
        if (func == "@add") {
            //create the path
            const _path = path.join(
                path.dirname(pathName),
                param1
            ).replace("\r", "")
            //add and parse file
            return parseCode(fs.readFileSync(_path, "utf-8"), _path)
        }
        //parse the imports
        else if (func == "@imp") {
            //parse the word in the line
            const lineParts = line.split(" ");
            //parse the import string
            const _import = lineParts.slice(1, lineParts.length).join("");
            //return the statement
            return `#include <${_import}>`
        }
        //check if the line includes a function statement
        else if (func == "@fn") {
            //line parts
            var lineParts = line.split(" ")
            //parts without func
            const parts = lineParts.slice(1, lineParts.length - 1).join(" ")
            //parse the base and the arguments
            const [base, args] = parts.split(":")
            //parse the functionName and the type
            const [name, type] = base.split("#")
            //set the function line
            return `${type} ${name}(${(args ?? "").split("{").join("")}) {`;
        }//check if the line includes a function statement
        else if (func == "@back") {
            //parse the words in the line
            const lineParts = line.split(" ");
            //parse the return string
            const returnVal = lineParts.slice(1, lineParts.length).join(" ");
            return `return ${returnVal};`;
        }
        //parse the global static
        else if (func == "@static") {
            //parse the line
            const lineParts = line.split(" ")
            //set the import string
            return `#define ${param1} ${lineParts.slice(2, lineParts.length).join(" ")}`
        }
        //for loop statement
        else if (func == "@loop") {
            //index name
            var indexName = param2 == "{" ? "index" : param2
            //set the statement
            return `for (int ${indexName} = 0; ${indexName} < ${param1}; ${indexName}++) {`;
        }
        //create array statement
        else if (func == "@array") {
            return `vector<${param3}> ${param1};`
        }
        //create array statement
        else if (func == "@for_each") {
            return `for (auto &${param1} : ${param3}) {`
        }

        else return line

    }).join("\n")

    return code;
}