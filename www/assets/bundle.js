---
---

var body = document.getElementsByTagName("body")[0];
var offcanvas = document.getElementById("offcanvas");
var backdrop = document.getElementById("backdrop");

function offcanvasShow() {
  if (!offcanvas || !body || !backdrop) return;
  offcanvas.classList.add("show");
  offcanvas.style.visibility = "visible";
  body.style.overflow = "hidden";
  backdrop.classList.add("show");
  backdrop.classList.remove("visually-hidden");
};

function offcanvasHide() {
  if (!offcanvas || !body || !backdrop) return;
  offcanvas.classList.remove("show");
  offcanvas.style.visibility = "hidden";
  body.style.overflow = "auto";
  backdrop.classList.remove("show");
  backdrop.classList.add("visually-hidden");
};

var toggle = document.getElementById("offcanvas-toggle");
if (toggle) toggle.addEventListener("click", offcanvasShow);
var close = document.getElementById("offcanvas-close");
if (close) close.addEventListener("click", offcanvasHide);
if (backdrop) backdrop.addEventListener("click", offcanvasHide);
