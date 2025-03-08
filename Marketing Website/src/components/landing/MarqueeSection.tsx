
import { FC } from "react";

const MarqueeSection: FC = () => {
  const partners = [
    "/lovable-uploads/1418d20f-c9b0-4a51-acba-e552b41096ed.png",
    "/lovable-uploads/ffc856cc-a362-4ad7-a572-06ce1f5b88e8.png",
    "/lovable-uploads/315a65f6-c12f-4fd7-a05e-72bf555cda29.png",
    "/lovable-uploads/8bdbbd8b-9ac4-4149-ab84-35a5da494cdd.png",
    "/lovable-uploads/af682212-6c39-405f-aabd-0f6937dba391.png",
    "/lovable-uploads/4cc4174c-f936-493f-b36d-6f5f6de3314e.png",
    "/lovable-uploads/fb9d7d1a-7fba-43f6-831c-f0bbae19c847.png",
    "/lovable-uploads/e83ff2bb-07fc-45d0-a094-0c14e0f8579b.png",
    "/lovable-uploads/b637482e-8bcb-43f1-8c85-ec2a0f0e0d68.png",
    "/lovable-uploads/c273f2a7-ebd6-4e83-be5a-1aa2442185a3.png",
    "/lovable-uploads/eb57a849-36c9-4032-994e-fb4c678a9d1b.png"
  ];

  return (
    <section className="py-20 bg-brand-500">
      <div className="container mx-auto px-6 text-center mb-12">
        <h2 className="text-4xl font-bold mb-4 text-white">Our Research Partners</h2>
        <p className="text-xl text-white/90">
          Collaborating with leading Companies and Institutions to advance maternal healthcare
        </p>
      </div>
      
      <div className="relative w-full overflow-hidden">
        <div className="w-[calc(220px*22+3rem*22)] flex animate-marquee gap-12">
          <div className="flex shrink-0 items-center gap-12">
            {partners.map((logo, index) => (
              <div
                key={`first-${index}`}
                className="w-[220px] flex-shrink-0"
              >
                <div className="w-full h-[110px] bg-white rounded-lg p-5 flex items-center justify-center hover:shadow-xl transition-all duration-300">
                  <img
                    src={logo}
                    alt={`Partner ${index + 1}`}
                    className={`w-full h-full ${index === 6 ? 'object-contain scale-125' : 'object-contain'}`}
                    loading="lazy"
                  />
                </div>
              </div>
            ))}
          </div>
          <div className="flex shrink-0 items-center gap-12">
            {partners.map((logo, index) => (
              <div
                key={`second-${index}`}
                className="w-[220px] flex-shrink-0"
              >
                <div className="w-full h-[110px] bg-white rounded-lg p-5 flex items-center justify-center hover:shadow-xl transition-all duration-300">
                  <img
                    src={logo}
                    alt={`Partner ${index + 1}`}
                    className={`w-full h-full ${index === 6 ? 'object-contain scale-125' : 'object-contain'}`}
                    loading="lazy"
                  />
                </div>
              </div>
            ))}
          </div>
        </div>
      </div>
    </section>
  );
};

export default MarqueeSection;
