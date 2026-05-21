# Day 01 - Infrastructure and Project Setup

## Status
- State: Completed
- Date: 19/05/2026
- Hours Worked: 4h
- Main Focus: Prepare the development pipeline before Unreal implementation.

## Planned Tasks
- [x] Confirm GitHub repository structure
- [x] Confirm GitHub Pages dashboard works
- [x] Confirm Obsidian vault structure
- [x] Create project workflow notes
- [x] Prepare UE5 project setup checklist
- [x] Capture evidence of repository/site setup

## Work Completed
- [x] GitHub repository created
- [x] Repository made public for GitHub Pages
- [x] GitHub Pages dashboard deployed
- [x] Obsidian folder structure created
- [x] Site demo data cleaned
- [x] Day 01 worksheet prepared

## Technical Notes
The project repository was initialized using GitHub and configured for public GitHub Pages deployment. The documentation workflow was designed around Obsidian as the primary writing environment and GitHub as the version-controlled publication platform.

A structured folder hierarchy was created to separate daily logs, worksheets, research material, architecture notes, screenshots, benchmarks, assets and thesis documentation. A website dashboard was integrated into the repository and configured for deployment through GitHub Pages.

The website architecture was modified to operate from the `/docs` directory to comply with GitHub Pages deployment restrictions. The dashboard was configured to read project progress from JSON data files and provide public access to development evidence.

## Problems Encountered
Example:
- GitHub Pages only supported deployment from `/root` or `/docs`, requiring relocation of the website files.
- Empty repository folders were not visible on GitHub because Git does not track empty directories.
- Initial confusion existed between the repository root and the website deployment structure.
- Progress data was initially updated in the wrong JSON file due to the existence of multiple data locations.
- Evidence screenshots required additional organization to support future public presentation.

## Solutions / Decisions
Example:
- The website deployment target was standardized to the `/docs` directory.
- README files were added to repository folders so they would be tracked by Git.
- Obsidian was selected as the primary documentation environment.
- Daily development evidence would be published through GitHub Pages after completion of each workday.
- Project progress would be maintained through `docs/data/progress.json`.
- Screenshot evidence would be organized by day to simplify traceability and future dissertation references.
- The repository structure was finalized before beginning Unreal Engine implementation work.
## Evidence Captured
- Screenshot: GitHub repository structure
- Screenshot: GitHub Pages deployment settings
- Screenshot: Public dashboard deployment
- Screenshot: Obsidian vault structure
- Screenshot: Repository folder organization
- Commit: Initial infrastructure and documentation pipeline setup

## Dissertation Notes
This day establishes the documentation and evidence pipeline for the project. It supports the dissertation by creating a traceable development process and making the technical work reproducible and reviewable.

## Tomorrow
- [ ] Create UE5.7.4 C++ project
- [ ] Configure Unreal project folders
- [ ] Enable required Unreal plugins
- [ ] Create initial C++ module/class structure
