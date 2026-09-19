document.addEventListener("DOMContentLoaded", () => {
    const facts = [
        'The term "artificial intelligence" was coined in 1956.',
        "Machine learning is a branch of artificial intelligence.",
        "AI can be used to recognize images and understand language.",
        "Some AI systems can generate text, images, music, and video.",
        "AI can help scientists analyze enormous amounts of data.",
        "Recommendation systems use AI to suggest content to users.",
        "Neural networks are inspired by the structure of the human brain.",
        "AI is used in navigation systems and traffic prediction.",
        "Computer vision allows machines to process and interpret images.",
        "AI systems can learn from data and improve their predictions over time."
    ];

    const button = document.getElementById("button");
    const fact = document.getElementById("fact");

    button.addEventListener("click", () => {
        let rnum = Math.floor(Math.random() * facts.length);
        fact.textContent = facts[rnum];
    });
});
