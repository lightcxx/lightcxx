// @ts-ignore
import { walk } from "https://deno.land/std/fs/mod.ts";

class Section {
    tag: string;
    children: Section[];

    constructor(tag: string) {
        this.tag = tag;
        this.children = [];
    }
}

const sections: {[key: string]: Section} = {};
const topLevelSections: Section[] = [];

// @ts-ignore
for await (const entry of walk(Deno.args[0])) {
    if (entry.isDirectory) {
        const lastSlash = entry.path.lastIndexOf("/");
        if (lastSlash < 0) {
            continue;
        }
        const sectionTag = entry.path.substring(lastSlash + 1);
        if (sections[sectionTag] == null) {
            sections[sectionTag] = new Section(sectionTag);
        }
        const pathWithoutLastDir = entry.path.substring(0, lastSlash);
        const beforeLastSlash = pathWithoutLastDir.lastIndexOf("/");
        if (beforeLastSlash < 0) {
            topLevelSections.push(sections[sectionTag]);
            continue;
        }
        const parentSectionTag = pathWithoutLastDir.substr(beforeLastSlash + 1);
        if (sections[parentSectionTag] == null) {
            sections[parentSectionTag] = new Section(parentSectionTag);
        }
        sections[parentSectionTag].children.push(sections[sectionTag]);
    }
}

const printSection = (section: Section, depth: number) => {
    // @ts-ignore
    console.log(`${' '.repeat(depth)}${section.tag}`);
    for (const child of section.children.sort((a, b) => a.tag.localeCompare(b.tag))) {
        printSection(child, depth + 2);
    }
}
for (const section of topLevelSections.sort((a, b) => a.tag.localeCompare(b.tag))) {
    printSection(section, 0);
}
