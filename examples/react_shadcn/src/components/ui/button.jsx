import { Slot } from "@radix-ui/react-slot";
import { cva } from "class-variance-authority";

import { cn } from "@/lib/utils";

const button_variants = cva(
  "inline-flex items-center justify-center rounded-full text-sm font-semibold transition-colors focus-visible:outline-none focus-visible:ring-2 focus-visible:ring-ring focus-visible:ring-offset-2 disabled:pointer-events-none disabled:opacity-50 ring-offset-background",
  {
    variants: {
      variant: {
        default: "bg-primary px-5 py-3 text-primary-foreground hover:bg-primary/90",
        secondary: "bg-secondary px-5 py-3 text-secondary-foreground hover:bg-secondary/90",
        outline: "border border-border px-5 py-3 text-foreground hover:bg-secondary/60"
      }
    },
    defaultVariants: {
      variant: "default"
    }
  }
);

export function Button({ className, variant, asChild = false, ...props }) {
  const Comp = asChild ? Slot : "button";

  return <Comp className={cn(button_variants({ variant }), className)} {...props} />;
}
