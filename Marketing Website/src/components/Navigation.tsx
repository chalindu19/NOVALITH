
import { useState, useEffect, FC } from "react";
import { Menu, X } from "lucide-react";
import { useNavigate } from "react-router-dom";

const Navigation: FC = () => {
  const [isMenuOpen, setIsMenuOpen] = useState(false);
  const [isScrolled, setIsScrolled] = useState(false);
  const navigate = useNavigate();

  useEffect(() => {
    const handleScroll = () => {
      setIsScrolled(window.scrollY > 50);
    };

    window.addEventListener("scroll", handleScroll);
    return () => window.removeEventListener("scroll", handleScroll);
  }, []);

  const scrollToSection = (id: string) => {
    if (window.location.pathname !== "/") {
      navigate("/");
      setTimeout(() => {
        window.scrollTo({ top: 0, behavior: "smooth" });
        const element = document.getElementById(id);
        if (element) {
          element.scrollIntoView({ behavior: "smooth" });
        }
      }, 100);
    } else {
      const element = document.getElementById(id);
      if (element) {
        element.scrollIntoView({ behavior: "smooth" });
      }
    }
    setIsMenuOpen(false);
  };

  const navigateToPage = (path: string) => {
    navigate(path);
    window.scrollTo({ top: 0, behavior: 'smooth' });
    setIsMenuOpen(false);
  };

  const goToHome = () => {
    navigate('/');
    window.scrollTo({ top: 0, behavior: 'smooth' });
    setIsMenuOpen(false);
  };

  return (
    <nav
      className={`fixed top-0 left-0 right-0 z-50 transition-all duration-300 ${
        isScrolled ? "bg-white/95 backdrop-blur-sm shadow-md" : "bg-white/5 backdrop-blur-sm"
      }`}
    >
      <div className="container mx-auto px-6 py-4">
        <div className="flex items-center justify-between">
          <button
            onClick={goToHome}
            className="focus:outline-none transform hover:scale-105 transition-transform duration-300"
          >
            <img
              src="/lovable-uploads/f9f54235-5fd4-4b13-8388-7d8162b480ba.png"
              alt="Amor Developers Group"
              className="h-12 w-auto"
            />
          </button>

          <div className="hidden md:flex items-center space-x-12">
            <button
              onClick={() => scrollToSection("features")}
              className={`transition-colors hover:scale-105 transform duration-300 ${
                isScrolled ? "text-brand-600" : "text-white"
              } hover:text-brand-400`}
            >
              Features
            </button>
            <button
              onClick={() => navigateToPage("/design")}
              className={`transition-colors hover:scale-105 transform duration-300 ${
                isScrolled ? "text-brand-600" : "text-white"
              } hover:text-brand-400`}
            >
              Design
            </button>
            <button
              onClick={() => navigateToPage("/about")}
              className={`transition-colors hover:scale-105 transform duration-300 ${
                isScrolled ? "text-brand-600" : "text-white"
              } hover:text-brand-400`}
            >
              About
            </button>
            <button
              onClick={() => scrollToSection("contact")}
              className={`transition-colors hover:scale-105 transform duration-300 ${
                isScrolled ? "text-brand-600" : "text-white"
              } hover:text-brand-400`}
            >
              Contact
            </button>
          </div>

          <button
            className={`md:hidden ${isScrolled ? "text-brand-600" : "text-white"}`}
            onClick={() => setIsMenuOpen(!isMenuOpen)}
          >
            {isMenuOpen ? <X size={24} /> : <Menu size={24} />}
          </button>
        </div>

        {isMenuOpen && (
          <div className="md:hidden absolute top-full left-0 right-0 bg-white/95 backdrop-blur-sm shadow-lg py-4 animate-fade-in">
            <div className="flex flex-col space-y-4 px-6">
              <button
                onClick={() => scrollToSection("features")}
                className="text-brand-600 hover:text-brand-800 transition-colors text-left hover:translate-x-2 transform duration-300"
              >
                Features
              </button>
              <button
                onClick={() => navigateToPage("/design")}
                className="text-brand-600 hover:text-brand-800 transition-colors text-left hover:translate-x-2 transform duration-300"
              >
                Design
              </button>
              <button
                onClick={() => navigateToPage("/about")}
                className="text-brand-600 hover:text-brand-800 transition-colors text-left hover:translate-x-2 transform duration-300"
              >
                About
              </button>
              <button
                onClick={() => scrollToSection("contact")}
                className="text-brand-600 hover:text-brand-800 transition-colors text-left hover:translate-x-2 transform duration-300"
              >
                Contact
              </button>
            </div>
          </div>
        )}
      </div>
    </nav>
  );
};

export default Navigation;
