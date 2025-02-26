
import { FC, useEffect, useState } from "react";
import { ChevronLeft, ChevronRight } from "lucide-react";

const SolutionCarousel: FC = () => {
  const [currentSlide, setCurrentSlide] = useState(0);

  const slides = [
    {
      url: "/lovable-uploads/0856f641-2563-466c-b254-ca239cfbdb91.png",
      alt: "Smart Belly Wrap Demo"
    },
    {
      url: "/lovable-uploads/5f2b9b0f-a380-46d4-88da-ad3eb2ac237f.png",
      alt: "Smart Belly Wrap in Pink"
    },
    {
      url: "/lovable-uploads/02948680-38f8-4569-91d7-f9a204541504.png",
      alt: "Smart Belly Wrap in White"
    }
  ];

  useEffect(() => {
    const timer = setInterval(() => {
      setCurrentSlide((prev) => (prev + 1) % slides.length);
    }, 4000); // Change slide every 4 seconds

    return () => clearInterval(timer);
  }, []);

  const goToSlide = (index: number) => {
    setCurrentSlide(index);
  };

  const nextSlide = () => {
    setCurrentSlide((prev) => (prev + 1) % slides.length);
  };

  const prevSlide = () => {
    setCurrentSlide((prev) => (prev - 1 + slides.length) % slides.length);
  };

  return (
    <div className="relative group">
      {/* Image Container */}
      <div className="relative h-[400px] md:h-[500px] overflow-hidden rounded-lg">
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
              className="w-full h-full object-cover rounded-lg shadow-xl"
            />
          </div>
        ))}
      </div>

      {/* Navigation Arrows */}
      <button
        onClick={prevSlide}
        className="absolute left-2 top-1/2 -translate-y-1/2 bg-white/80 hover:bg-white p-2 rounded-full shadow-lg opacity-0 group-hover:opacity-100 transition-opacity duration-300"
        aria-label="Previous slide"
      >
        <ChevronLeft className="h-6 w-6 text-brand-600" />
      </button>
      <button
        onClick={nextSlide}
        className="absolute right-2 top-1/2 -translate-y-1/2 bg-white/80 hover:bg-white p-2 rounded-full shadow-lg opacity-0 group-hover:opacity-100 transition-opacity duration-300"
        aria-label="Next slide"
      >
        <ChevronRight className="h-6 w-6 text-brand-600" />
      </button>

      {/* Slide Indicators */}
      <div className="absolute bottom-4 left-0 right-0 flex justify-center gap-2">
        {slides.map((_, index) => (
          <button
            key={index}
            onClick={() => goToSlide(index)}
            className={`h-2 transition-all duration-300 rounded-full ${
              currentSlide === index ? "w-8 bg-brand-500" : "w-2 bg-brand-500/50"
            }`}
            aria-label={`Go to slide ${index + 1}`}
          />
        ))}
      </div>
    </div>
  );
};

export default SolutionCarousel;
