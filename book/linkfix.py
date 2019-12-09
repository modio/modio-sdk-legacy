#!/usr/bin/env python3
import json
import re
import sys

"""Match [[File]] and [[Title|File]]"""
WIKI_LINK = re.compile('(?:\[\[(?:(.*)\|)?(.*)\]\])')

def replace_links(content):
    def repl(m):
        (title, filename) = m.group(1, 2)

        title = title if title else filename
        filename = filename.strip().replace(' ', '-').replace('::', '__')

        return "[%s](%s.md)" % (title.strip(), filename)

    return WIKI_LINK.sub(repl, content)

def walk_book(section, func):
    if 'Chapter' not in section:
        return

    content = section['Chapter']['content'];
    content = func(content)
    section['Chapter']['content'] = content

    for section in section['Chapter']['sub_items']:
        walk_book(section, func)

def main():
    if len(sys.argv) > 1 and sys.argv[1] == 'supports':
        exit(0)

    if len(sys.argv) > 1 and sys.argv[1] == 'summary':
        content = sys.stdin.buffer.read().decode('utf-8')
        """
        Every chapter must contain a link.
        Change every `* Foobar` to `* [[Foobar]]`.
        """
        content = re.sub('\* ([A-Za-z ]+)', lambda m: "* [[%s]]" % m.group(1), content)
        print(replace_links(content))
        exit(0)

    raw = sys.stdin.buffer.read()
    [context, book] = json.loads(raw.decode('utf-8'))

    for section in book['sections']:
        walk_book(section, replace_links)

    json.dump(book, sys.stdout)
    exit(0)

if __name__ == '__main__':
    main()
