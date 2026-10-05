// Script Kustom untuk AlgoBlog

document.addEventListener("DOMContentLoaded", function() {
    // Menambahkan fungsi pencarian sederhana yang hanya memunculkan alert (sebagai mockup)
    const searchBtn = document.getElementById("button-search");
    if(searchBtn) {
        searchBtn.addEventListener("click", function() {
            const input = document.querySelector(".input-group input").value;
            if(input.trim() !== "") {
                alert("Pencarian untuk: " + input + "\n(Fitur backend belum diimplementasikan)");
            } else {
                alert("Silakan masukkan kata kunci pencarian!");
            }
        });
    }

    console.log("AlgoBlog Script Dimuat dengan Sukses!");
});
