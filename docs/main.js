let completedDays = [];

function dayNumber(value) {
  const match = String(value || "").match(/\d+/);
  return match ? Number(match[0]) : 0;
}

function normalizeHours(value) {
  const match = String(value || "").match(/[\d.]+/);
  return match ? Number(match[0]) : 0;
}

function renderDays() {
  const target = document.getElementById("dailyLogs");
  const query = document.getElementById("searchInput").value.toLowerCase();
  const sort = document.getElementById("sortSelect").value;

  let days = [...completedDays].filter(day => {
    const text = `${day.title || ""} ${day.summary || ""} ${day.date || ""}`.toLowerCase();
    return text.includes(query);
  });

  days.sort((a, b) => {
    if (sort === "oldest") return String(a.date).localeCompare(String(b.date));
    if (sort === "newest") return String(b.date).localeCompare(String(a.date));
    if (sort === "dayAsc") return dayNumber(a.title) - dayNumber(b.title);
    if (sort === "dayDesc") return dayNumber(b.title) - dayNumber(a.title);
    if (sort === "hoursDesc") return normalizeHours(b.hours) - normalizeHours(a.hours);
    return 0;
  });

  if (!days.length) {
    target.innerHTML = `<div class="empty">No completed daily entries yet. When Day 01 is finished, it will appear here after you update <code>docs/data/progress.json</code>, commit, and push.</div>`;
    return;
  }

  target.innerHTML = days.map(day => `
    <article class="day-card">
      <header>
        <h3>${day.title}</h3>
        <span class="badge">${day.completion || "Completed"}</span>
      </header>
      <div class="meta">
        <span>${day.date || "No date"}</span>
        <span>${day.hours || "0h"}</span>
      </div>
      <p class="summary">${day.summary || ""}</p>
      <div class="links">
        ${day.log ? `<a href="${day.log}">Daily log</a>` : ""}
        ${day.evidence ? `<a href="${day.evidence}">Evidence</a>` : ""}
      </div>
    </article>
  `).join("");
}

async function loadProgress() {
  try {
    const response = await fetch("./data/progress.json", { cache: "no-store" });
    const data = await response.json();
    completedDays = data.completedDays || [];

    document.getElementById("projectStatus").textContent = data.status || "Active";
    document.getElementById("completedCount").textContent = completedDays.length;
    document.getElementById("totalHours").textContent =
      `${completedDays.reduce((sum, day) => sum + normalizeHours(day.hours), 0)}h`;

    renderDays();
  } catch (error) {
    document.getElementById("projectStatus").textContent = "Data error";
    document.getElementById("dailyLogs").innerHTML =
      `<div class="empty">Could not load dashboard data. Check <code>docs/data/progress.json</code>.</div>`;
    console.error(error);
  }
}

document.getElementById("searchInput").addEventListener("input", renderDays);
document.getElementById("sortSelect").addEventListener("change", renderDays);

loadProgress();
