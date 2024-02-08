const { log } = require("console")
const fs = require("fs")
const path = require("path")

const inpPath = "code/index.at"
const outPath = "C:\\Users\\Manuel Westermeier\\source\\repos\\cpp-server-script\\cpp-server-script.cpp"

//start compiling
fs.writeFileSync(outPath,
    fs.readFileSync("src/index.cpp", "utf-8") + parseFile(inpPath)
    , "utf-8")

function parseFile(pathname = "") {

    const dir = path.dirname(pathname)

    return fs.readFileSync(pathname, "utf-8").split("\n").map(line => {
        //check if the nostrinp part includes @
        if (!line.split("\"").filter((p, i) => i % 2 == 0).join(" ").includes("@")) return line
        //create the out string
        var out = ""
        //parse the paths
        const parts = line.split("\"").map((part, i) => {
            const isStr = (2 % i == 0)
            return { part, isStr }
        })
        //parse the output
        parts.forEach(({ isStr, part }) => {
            //add the string
            if (isStr) {
                out += `"${part}"`
                return
            }
            //path parts
            const parsedParts = part.split("  ").join(" ").split("\t").join(" ").split("\r").join("").split(" ").filter(p => p != "");
            const [fn] = parsedParts;
            //start the logic
            //on init
            if (fn == "@init") {
                out += "int main() {"
            }
            //import form file
            else if (fn == "@imp") {
                //get the path
                const impPath = path.join(dir, parsedParts[1].replace("\r", ""));
                if (impPath == pathname) return;
                if (fs.existsSync(impPath))
                    out += parseFile(impPath);
            }
            //create array
            else if (fn == "@array") {
                out += `vector<${parsedParts[3]}> ${parsedParts[1]};`
            }
            //loop for each
            else if (fn == "@foreach") {
                out += `for (auto ${parsedParts[1]} : ${parsedParts[3]}) {`
            }
            //destructure arrays
            else if (fn == "@destr") {
                for (let index = 0; index < parsedParts.length - 5; index++) {
                    out += `${parsedParts[3]} ${parsedParts[index + 5]} = ${parsedParts[1]}.at(${index});\n`
                }
            }
            //create a dictionary
            else if (fn == "@map") {
                out += `map<${parsedParts[3] ?? "string"}, ${parsedParts[5] ?? "string"}> ${parsedParts[1]};`
            }
            //loop for int
            else if (fn == "@loop") {
                out += `for (int ${parsedParts[3] || "index"} = 0; ${parsedParts[3] || "index"} < ${parsedParts[1]}; ${parsedParts[3] || "index"}++) {`
            }
            //create function
            else if (fn == "@fn") {
                const [name, type] = parsedParts[1].split("#")
                out += `${type || "void"} ${name} ${parsedParts.slice(2, parsedParts.length).join(" ")}`
            }
            //create template strings
            else if (fn == "@templ") {
                const impPath = path.join(dir, parsedParts[3].replace("\r", ""));
                if (impPath == pathname) return;
                if (!fs.existsSync(impPath)) throw new Error("path not exists");
                const template = createTemplate(impPath, parsedParts.splice(5, parsedParts.length - 1), parsedParts);
                out += template;
            }
            //return default
            else {
                log(fn)
                out += parsedParts.join(" ");
            }
        })
        //
        return out
    }).join("\n")

}

function createTemplate(pathname, params = [], parsedParts) {
    const data = fs.readFileSync(pathname, "utf-8");
    var isVar = false;
    var template = `string ${parsedParts[1]};\n`;
    data.split("#").map((part, i) => {
        if (isVar) {
            template += `${parsedParts[1]} += ${params[parseInt(part)] ?? '""'};\n`
        }
        else {
            const noLines = part.split('"').join('\\"').split("\n").join('\\n').split("\r").join('\\r')
            template += `${parsedParts[1]} += "${noLines}";\n`
        }
        isVar = !isVar;
    })
    return template;
}