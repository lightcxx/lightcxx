// @ts-ignore
import jsdom from "https://dev.jspm.io/jsdom";

const topLevelTags = ["support", "utilities"];

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
    const dom = new jsdom.JSDOM(bodyText);
    const topLevelSections: Section[] = [];
    for (const topLevelSectionTag of topLevelTags) {
        const topLevelSection = new Section(`[${topLevelSectionTag}]`);
        findSections(dom.window.document.querySelector(`#${topLevelSectionTag}`), topLevelSection);
        topLevelSections.push(topLevelSection);
    }
    for (const section of topLevelSections.sort((a, b) => a.tag.localeCompare(b.tag))) {
        printSection(section, 0);
    }
}

main().then(() => {
});
