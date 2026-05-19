async function loadProgress() {
  const statusText = document.getElementById("statusText");
  const dailyLogs = document.getElementById("dailyLogs");

  try {
    const response = await fetch("./data/progress.json", { cache: "no-store" });
    const data = await response.json();

    statusText.textContent = `${data.status}: ${data.message}`;

    if (!data.completedDays || data.completedDays.length === 0) {
      dailyLogs.innerHTML = `<div class="empty">No completed days yet. Finish Day 01, update progress.json, commit, and push to publish it here.</div>`;
      return;
    }

    dailyLogs.innerHTML = data.completedDays.map(day => `
      <article class="day-card">
        <h3>${day.title}</h3>
        <p><strong>Date:</strong> ${day.date}</p>
        <p><strong>Hours:</strong> ${day.hours}</p>
        <p><strong>Completion:</strong> ${day.completion}</p>
        <p>${day.summary}</p>
        ${day.log ? `<p><a href="${day.log}">Open daily log</a></p>` : ""}
        ${day.worksheet ? `<p><a href="${day.worksheet}">Open worksheet</a></p>` : ""}
      </article>
    `).join("");
  } catch (error) {
    statusText.textContent = "Could not load progress data.";
    dailyLogs.innerHTML = `<div class="empty">Check docs/data/progress.json.</div>`;
    console.error(error);
  }
}

loadProgress();
