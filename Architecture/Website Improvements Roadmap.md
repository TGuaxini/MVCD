
## Planned Refactors

### Dynamic Evidence Gallery System
Current implementation uses:
- individual `index.html` files per screenshot day folder.

Example:
docs/assets/screenshots/Day_01/index.html

This works for early development but is not scalable long-term.

Planned replacement:
- reusable gallery viewer system,
- dynamic image loading,
- automatic gallery generation,
- fullscreen preview support,
- benchmark comparison support,
- destruction before/after visualization.

Target future structure:
gallery.html?day=Day_01

Benefits:
- eliminates repeated HTML files,
- simplifies publishing workflow,
- improves scalability for benchmark-heavy documentation.