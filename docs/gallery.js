function prettyName(filePath) {
  const file = filePath.split("/").pop() || filePath;
  return file
    .replace(/\.[^/.]+$/, "")
    .replaceAll("_", " ")
    .replaceAll("-", " ");
}

async function loadGallery() {
  const params = new URLSearchParams(window.location.search);
  const day = params.get("day");

  const titleEl = document.getElementById("galleryTitle");
  const descEl = document.getElementById("galleryDescription");
  const contentEl = document.getElementById("galleryContent");

  if (!day) {
    titleEl.textContent = "No Day Selected";
    contentEl.innerHTML = "<p>No gallery day was provided.</p>";
    return;
  }

  try {
    const response = await fetch("./data/evidence.json", { cache: "no-store" });
    const data = await response.json();
    const gallery = data[day];

    if (!gallery) {
      titleEl.textContent = `${day} Evidence Not Found`;
      contentEl.innerHTML = `<p>No evidence data exists for <code>${day}</code>. Run the evidence generation script and push again.</p>`;
      return;
    }

    titleEl.textContent = gallery.title || `${day} Evidence`;
    descEl.textContent = gallery.description || "Project evidence screenshots.";

    const images = gallery.images || [];
    if (!images.length) {
      contentEl.innerHTML = `<p>No screenshots found for <code>${day}</code>.</p>`;
      return;
    }

    contentEl.innerHTML = `
      <div class="evidence-grid">
        ${images.map(img => `
          <article class="evidence-card">
            <a href="${img.file}" target="_blank" rel="noopener">
              <img src="${img.file}" alt="${img.caption || prettyName(img.file)}" loading="lazy">
            </a>
            <div class="evidence-caption">
              ${img.caption || prettyName(img.file)}
            </div>
          </article>
        `).join("")}
      </div>
    `;
  } catch (error) {
    titleEl.textContent = "Gallery Error";
    contentEl.innerHTML = "<p>Could not load evidence data. Check <code>docs/data/evidence.json</code>.</p>";
    console.error(error);
  }
}

loadGallery();
