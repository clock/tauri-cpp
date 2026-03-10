import { useEffect, useState } from "react";
import { Cpu, Rocket } from "lucide-react";

import { Button } from "@/components/ui/button";

const tauri_core = window.__TAURI__;

export function App() {
  const [output, set_output] = useState("waiting for startup event");

  useEffect(() => {
    if (!tauri_core?.event?.listen)
      return;

    let unlisten;

    tauri_core.event.listen("demo:start", event => {
      set_output(JSON.stringify(event.payload, null, 2));
    }).then(callback => {
      unlisten = callback;
    });

    return () => {
      if (unlisten)
        unlisten();
    };
  }, []);

  const invoke_command = async command => {
    if (!tauri_core?.core?.invoke)
      return set_output("tauri runtime not found");

    const result = await tauri_core.core.invoke(command, {
      payloadJson: JSON.stringify({ source: "react_shadcn" })
    });

    set_output(JSON.stringify(result, null, 2));
  };

  return (
    <main className="min-h-screen bg-background text-foreground">
      <section className="mx-auto flex min-h-screen max-w-6xl flex-col justify-center gap-8 px-6 py-16">
        <div className="grid gap-6 lg:grid-cols-[1.25fr_0.9fr]">
          <article className="rounded-[2rem] border border-border/60 bg-card/80 p-8 shadow-2xl shadow-black/20 backdrop-blur">
            <p className="text-sm uppercase tracking-[0.35em] text-muted-foreground">react shadcn</p>
            <h1 className="mt-4 text-5xl font-black tracking-tight sm:text-7xl">tauri-cpp</h1>
            <p className="mt-4 max-w-2xl text-lg text-muted-foreground">
              a higher level example with React, shadcn/ui patterns, and the same thin native demo
              bridge as the other apps.
            </p>
            <div className="mt-8 flex flex-wrap gap-3">
              <Button onClick={() => void invoke_command("sync_echo")}>
                <Rocket className="mr-2 h-4 w-4" />
                sync command
              </Button>
              <Button variant="secondary" onClick={() => void invoke_command("async_echo")}>
                <Cpu className="mr-2 h-4 w-4" />
                async command
              </Button>
              <Button
                variant="outline"
                onClick={() => {
                  if (!tauri_core?.core?.invoke)
                    return set_output("tauri runtime not found");

                  void tauri_core.core.invoke("smoke_test").then(result => {
                    set_output(typeof result === "string" ? result : JSON.stringify(result, null, 2));
                  });
                }}
              >
                smoke test
              </Button>
            </div>
          </article>
          <aside className="rounded-[2rem] border border-border/60 bg-slate-950/80 p-6 shadow-xl shadow-black/20">
            <p className="text-sm uppercase tracking-[0.3em] text-cyan-300">output</p>
            <pre className="mt-4 overflow-auto rounded-3xl bg-black/30 p-5 text-sm text-cyan-50">
              {output}
            </pre>
          </aside>
        </div>
      </section>
    </main>
  );
}
