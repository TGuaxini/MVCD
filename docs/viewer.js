function escapeHtml(text) {
  return text.replaceAll("&", "&amp;").replaceAll("<", "&lt;").replaceAll(">", "&gt;");
}

function inlineMarkdown(text) {
  return escapeHtml(text)
    .replace(/\*\*(.*?)\*\*/g, "<strong>$1</strong>")
    .replace(/`([^`]+)`/g, "<code>$1</code>");
}

function renderMarkdown(md) {
  const lines = md.split(/\r?\n/);
  let html = "";
  let inList = false;
  let inCode = false;
  let codeBuffer = [];

  function closeList() {
    if (inList) {
      html += "</ul>";
      inList = false;
    }
  }

  function closeCode() {
    if (inCode) {
      html += `<pre><code>${escapeHtml(codeBuffer.join("\n"))}</code></pre>`;
      codeBuffer = [];
      inCode = false;
    }
  }

  for (const line of lines) {
    if (line.trim().startsWith("```")) {
      if (inCode) closeCode();
      else {
        closeList();
        inCode = true;
      }
      continue;
    }

    if (inCode) {
      codeBuffer.push(line);
      continue;
    }

    if (line.startsWith("# ")) {
      closeList();
      html += `<h1>${inlineMarkdown(line.slice(2))}</h1>`;
    } else if (line.startsWith("## ")) {
      closeList();
      html += `<h2>${inlineMarkdown(line.slice(3))}</h2>`;
    } else if (line.startsWith("### ")) {
      closeList();
      html += `<h3>${inlineMarkdown(line.slice(4))}</h3>`;
    } else if (/^- \[[ xX]\]/.test(line.trim())) {
      if (!inList) {
        html += "<ul class='task-list'>";
        inList = true;
      }
      const checked = line.includes("[x]") || line.includes("[X]");
      const content = line.replace(/^- \[[ xX]\]\s*/, "");
      html += `<li class="${checked ? "done" : ""}"><span class="check">${checked ? "✓" : ""}</span>${inlineMarkdown(content)}</li>`;
    } else if (line.trim().startsWith("- ")) {
      if (!inList) {
        html += "<ul>";
        inList = true;
      }
      html += `<li>${inlineMarkdown(line.trim().slice(2))}</li>`;
    } else if (line.trim() === "") {
      closeList();
    } else {
      closeList();
      html += `<p>${inlineMarkdown(line)}</p>`;
    }
  }

  closeList();
  closeCode();
  return html;
}

async function loadDocument() {
  const params = new URLSearchParams(window.location.search);
  const file = params.get("file");
  const type = params.get("type") || "Document";
  document.getElementById("docType").textContent = type;

  if (!file || file.includes("..")) {
    document.getElementById("docTitle").textContent = "Invalid document";
    document.getElementById("documentContent").innerHTML = "<p>The requested document path is invalid.</p>";
    return;
  }

  try {
    const response = await fetch(file, { cache: "no-store" });
    if (!response.ok) throw new Error("Document not found");
    const md = await response.text();
    const firstTitle = md.split(/\r?\n/).find(line => line.startsWith("# "));
    document.getElementById("docTitle").textContent = firstTitle ? firstTitle.replace("# ", "") : "MVCD Document";
    document.getElementById("documentContent").innerHTML = renderMarkdown(md);
  } catch (error) {
    document.getElementById("docTitle").textContent = "Document not found";
    document.getElementById("documentContent").innerHTML = "<p>This document could not be loaded. Check that the file exists inside the docs folder and that progress.json points to the correct path.</p>";
  }
}

loadDocument();
