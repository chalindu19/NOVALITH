
import { FC, useEffect, useState } from "react";

interface SlideImage {
  url: string;
  alt: string;
}

const HeroCarousel: FC = () => {
  const [currentSlide, setCurrentSlide] = useState(0);

  const slides: SlideImage[] = [
    {
      url: "/lovable-uploads/abae5814-d11d-4f2d-8e3b-9865b212e5f4.png",
      alt: "Doctor examining pregnant woman"
    },
    {
      url: "/lovable-uploads/402da448-2f8e-458a-b856-a85b255d2f7b.png",
      alt: "Smiling pregnant woman"
    },
    {
      url: "/lovable-uploads/5e4b4bdc-9375-435e-b695-ebbed7425f85.png",
      alt: "Doctor using stethoscope"
    },
    {
      url: "/lovable-uploads/84ed2525-1644-4157-8c49-bb92623fc934.png",
      alt: "Pregnant woman with support band"
    },
    {
      url: "/lovable-uploads/c6878e81-7b1c-4820-aad0-1297f0e90d28.png",
      alt: "Happy family with newborn"
    }
  ];

  useEffect(() => {
    const timer = setInterval(() => {
      setCurrentSlide((prev) => (prev + 1) % slides.length);
    }, 5000); // Change slide every 5 seconds

    return () => clearInterval(timer);
  }, []);

  return (
    <div className="absolute inset-0 w-full h-full">
      {slides.map((slide, index) => (
        <div
          key={index}
          className={`absolute inset-0 transition-opacity duration-1000 ${
            currentSlide === index ? "opacity-100" : "opacity-0"
          }`}
        >
          <img
            src={slide.url}
            alt={slide.alt}
            className="w-full h-full object-cover"
          />
        </div>
      ))}
      <div className="absolute inset-0 bg-gradient-to-r from-brand-600/80 to-brand-500/80" />
    </div>
  );
};

export default HeroCarousel;
