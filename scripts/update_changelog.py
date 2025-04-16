#! /usr/bin/env python3
import re
import os
from datetime import datetime

os.chdir(os.path.dirname(os.path.dirname(__file__)))

with open('CHANGELOG', 'r') as fp:
    content = fp.read()

with open('debian/changelog', 'w') as fp:
    lines = [line.strip() for line in content.split('OpenFEC.org project CHANGELOG')[0].split('----')
             if line.strip()]

    for line in lines:
        m = re.search(r'(\w+ \d+, \d{4}): (\S+) ([\d\.]+)', line)
        if not m:
            continue

        date_str, package_name, version = m.groups()

        date_obj = datetime.strptime(date_str, "%b %d, %Y")
        formatted_date = date_obj.strftime("%a, %d %b %Y 00:00:00 +0000")

        bullet_points = re.findall(r'- (.+?)(?=\n- |\n\n|$)', line, re.DOTALL)

        fp.write(f"{package_name} ({version}) unstable; urgency=low\n\n")

        for point in bullet_points:
            fp.write(f"  * {point.strip()}\n")

        fp.write("\n")
        fp.write(f" -- Roc Streaming authors <roc@freelists.org>  {formatted_date}\n\n")
