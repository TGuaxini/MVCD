# How to Publish a Completed Day to the Website

When a day is finished:

1. Move the daily log from:

```text
Daily Logs/Drafts/
```

to:

```text
Daily Logs/Completed/
```

2. Copy the completed log into:

```text
docs/logs/
```

or create a short public version there.

3. Add an entry to:

```text
docs/data/progress.json
```

Example:

```json
{
  "title": "Day 01 - Infrastructure and Project Setup",
  "date": "2026-05-19",
  "hours": "4h",
  "completion": "Completed",
  "summary": "Set up the GitHub repository, Obsidian vault, GitHub Pages dashboard, and daily production workflow.",
  "log": "./logs/Day_01.md",
  "worksheet": "./worksheets/Day_01_Worksheet.md",
  "evidence": "../Screenshots/Day_01/"
}
```

4. Commit and push.

The site will update after GitHub Pages redeploys.
