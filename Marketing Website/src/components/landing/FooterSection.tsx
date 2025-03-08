
import { FC } from "react";
import { Linkedin, Instagram, Phone, Mail, MapPin } from "lucide-react";
import { useNavigate } from "react-router-dom";

const FooterSection: FC = () => {
  const navigate = useNavigate();

  const navigateToPage = (path: string) => {
    navigate(path);
    window.scrollTo({ top: 0, behavior: 'smooth' });
  };

  const scrollToSection = (id: string) => {
    if (window.location.pathname !== "/") {
      navigate("/");
      setTimeout(() => {
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
  };

  return (
    <footer className="bg-brand-600 text-white py-12">
      <div className="container mx-auto px-6">
        <div className="grid md:grid-cols-4 gap-8">
          <div className="space-y-4">
            <img
              src="/lovable-uploads/f9f54235-5fd4-4b13-8388-7d8162b480ba.png"
              alt="Amor Developers Group"
              className="h-12 w-auto"
            />
            <p className="text-brand-100">
              Transforming maternal healthcare through innovation
            </p>
          </div>
          
          <div>
            <h4 className="font-semibold mb-4">Quick Links</h4>
            <ul className="space-y-2">
              <li>
                <button
                  onClick={() => scrollToSection("features")}
                  className="hover:text-brand-100 transition-colors"
                >
                  Features
                </button>
              </li>
              <li>
                <button
                  onClick={() => navigateToPage("/design")}
                  className="hover:text-brand-100 transition-colors"
                >
                  Design
                </button>
              </li>
              <li>
                <button
                  onClick={() => navigateToPage("/about")}
                  className="hover:text-brand-100 transition-colors"
                >
                  About
                </button>
              </li>
            </ul>
          </div>

          <div>
            <h4 className="font-semibold mb-4">Legal</h4>
            <ul className="space-y-2">
              <li>
                <button
                  onClick={() => navigateToPage("/privacy")}
                  className="hover:text-brand-100 transition-colors"
                >
                  Privacy Policy
                </button>
              </li>
              <li>
                <button
                  onClick={() => navigateToPage("/terms")}
                  className="hover:text-brand-100 transition-colors"
                >
                  Terms of Service
                </button>
              </li>
              <li>
                <button
                  onClick={() => navigateToPage("/faq")}
                  className="hover:text-brand-100 transition-colors"
                >
                  FAQ
                </button>
              </li>
            </ul>
          </div>

          <div>
            <h4 className="font-semibold mb-4">Contact</h4>
            <ul className="space-y-3">
              <li>
                <a 
                  href="tel:+94703636366"
                  className="flex items-center space-x-2 hover:text-brand-100 transition-colors group"
                >
                  <Phone strokeWidth={2} size={20} color="white" />
                  <span>(+94)70 363 6366</span>
                </a>
              </li>
              <li>
                <a 
                  href="mailto:amorhealthcarelk@gmail.com"
                  className="flex items-center space-x-2 hover:text-brand-100 transition-colors group"
                >
                  <Mail strokeWidth={2} size={20} color="white" />
                  <span>amorhealthcarelk@gmail.com</span>
                </a>
              </li>
              <li>
                <a 
                  href="https://maps.google.com/?q=435+Galle+Rd,+Colombo+00300"
                  target="_blank"
                  rel="noopener noreferrer"
                  className="flex items-center space-x-2 hover:text-brand-100 transition-colors group"
                >
                  <MapPin strokeWidth={2} size={20} color="white" />
                  <span>435 Galle Rd, Colombo 00300</span>
                </a>
              </li>
            </ul>
          </div>
        </div>

        <div className="border-t border-brand-500 mt-8 pt-8">
          <div className="flex flex-col md:flex-row md:items-center md:justify-between">
            <p className="text-brand-100 text-center md:text-left flex-grow">
              © {new Date().getFullYear()} Amor Developers Group. All rights reserved.
            </p>
            <div className="flex space-x-4 justify-center md:justify-end mt-4 md:mt-0">
              <a
                href="https://www.linkedin.com/company/amor-developers-group"
                target="_blank"
                rel="noopener noreferrer"
                className="hover:text-brand-100 transition-colors"
              >
                <Linkedin className="h-5 w-5" />
              </a>
              <a
                href="https://www.instagram.com/amordevlk/?utm_source=ig_web_button_share_sheet"
                target="_blank"
                rel="noopener noreferrer"
                className="hover:text-brand-100 transition-colors"
              >
                <Instagram className="h-5 w-5" />
              </a>
            </div>
          </div>
        </div>
      </div>
    </footer>
  );
};

export default FooterSection;
