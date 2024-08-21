document.addEventListener('DOMContentLoaded', () => {
    setActiveNavLink();
    addHoverEffect();
});

function setActiveNavLink() {
    const navLinks = document.querySelectorAll('.nav-link');
    const currentPath = window.location.pathname.split('/').pop();
    navLinks.forEach(link => {
        if (link.getAttribute('href') === currentPath) {
            link.classList.add('active');
        }
    });
}

function addHoverEffect() {
    const navLinks = document.querySelectorAll('.nav-link');
    navLinks.forEach(link => {
        link.addEventListener('mouseover', () => {
            const activeLink = document.querySelector('.nav-link.active');
            if (activeLink) {
                activeLink.classList.add('hovering');
            }
        });
        link.addEventListener('mouseout', () => {
            const activeLink = document.querySelector('.nav-link.active');
            if (activeLink) {
                activeLink.classList.remove('hovering');
            }
        });
    });
}
