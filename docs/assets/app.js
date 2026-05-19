async function loadPlan() {
  const res = await fetch('data/daily-plan.json');
  const days = await res.json();
  const phaseFilter = document.getElementById('phase-filter');
  [...new Set(days.map(d => d.phase))].forEach(phase => {
    const opt = document.createElement('option'); opt.value = phase; opt.textContent = phase; phaseFilter.appendChild(opt);
  });
  const statusFilter = document.getElementById('status-filter');
  function render() {
    const phase = phaseFilter.value, status = statusFilter.value;
    const filtered = days.filter(d => (phase === 'all' || d.phase === phase) && (status === 'all' || d.status === status));
    const done = days.filter(d => d.status === 'Done').length;
    document.getElementById('total-days').textContent = days.length;
    document.getElementById('done-days').textContent = done;
    document.getElementById('hours').textContent = days.reduce((s,d)=>s+d.hours,0);
    document.getElementById('progress').textContent = Math.round(done / days.length * 100) + '%';
    document.getElementById('day-list').innerHTML = filtered.map(d => `
      <article class="day-card">
        <h2>Day ${String(d.day).padStart(2,'0')} - ${d.goal}</h2>
        <div class="meta"><span class="badge">${d.phase}</span><span class="badge">${d.hours}h</span><span class="badge status ${d.status==='Done'?'done':''}">${d.status}</span></div>
        <h3>Objectives</h3><ul>${d.tasks.map(t=>`<li><input type="checkbox" /> ${t}</li>`).join('')}</ul>
        <h3>Documentation</h3><p>${d.documentation}</p>
        <h3>Evidence</h3><p>${d.evidence}</p>
        <p class="links"><a href="logs/Day_${String(d.day).padStart(2,'0')}_Log.md">Obsidian log</a><a href="worksheets/Day_${String(d.day).padStart(2,'0')}_Worksheet.pdf">Worksheet PDF</a></p>
      </article>`).join('');
  }
  phaseFilter.addEventListener('change', render); statusFilter.addEventListener('change', render); render();
}
loadPlan();
