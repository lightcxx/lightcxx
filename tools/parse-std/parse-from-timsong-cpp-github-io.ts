// @ts-ignore
import { DOMParser } from "https://deno.land/x/deno_dom/deno-dom-wasm.ts";

const topLevelTags = [
    "support",
    "concepts",
    "diagnostics",
    "utilities",
    "strings",
    "containers",
    "iterators",
    "ranges",
    "algorithms",
    "numerics",
    "time",
    "localization",
    "input\\.output",
    "re",
    "atomics",
    "thread",
];

class Section {
    tag: string;
    children: Section[];

    constructor(tag: string) {
        this.tag = tag;
        this.children = [];
    }
}

const findSections = (node: any, currentSection: Section) => {
    for (const child of node.children) {
        if (child.id) {
            const childSection = new Section(`[${child.id}]`);
            currentSection.children.push(childSection);
            findSections(child, childSection);
        } else {
            findSections(child, currentSection);
        }
    }
}

const printSection = (section: Section, depth: number) => {
    // @ts-ignore
    console.log(`${' '.repeat(depth)}${section.tag}`);
    for (const child of section.children.sort((a, b) => a.tag.localeCompare(b.tag))) {
        printSection(child, depth + 2);
    }
}

// @ts-ignore
async function main() {
    const body = await fetch("https://timsong-cpp.github.io/cppwp/n4861");
    const bodyText = await body.text();
    const dom = new DOMParser().parseFromString(bodyText, "text/html");
    const topLevelSections: Section[] = [];
    for (const topLevelSectionTag of topLevelTags) {
        const topLevelSection = new Section(`[${topLevelSectionTag}]`);
        findSections(dom.querySelector(`#${topLevelSectionTag}`), topLevelSection);
        topLevelSections.push(topLevelSection);
    }
    for (const section of topLevelSections.sort((a, b) => a.tag.localeCompare(b.tag))) {
        printSection(section, 0);
    }
}

main().then(() => {
});
