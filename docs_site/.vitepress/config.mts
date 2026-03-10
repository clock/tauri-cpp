import { defineConfig } from "vitepress";

export default defineConfig({
  base: "/tauri-cpp/",
  title: "tauri-cpp",
  description: "windows first tauri + c++ starter",
  cleanUrls: true,
  lastUpdated: true,
  themeConfig: {
    nav: [
      { text: "Get Started", link: "/guide/quickstart" },
      { text: "Examples", link: "/guide/examples" },
      { text: "Integrate", link: "/guide/existing-projects" },
      { text: "API", link: "/api/" },
      { text: "GitHub", link: "https://github.com/clock/tauri-cpp" }
    ],
    sidebar: [
      {
        text: "Start Here",
        items: [
          { text: "Quickstart", link: "/guide/quickstart" },
          { text: "Unix Setup", link: "/guide/unix-setup" },
          { text: "Examples", link: "/guide/examples" }
        ]
      },
      {
        text: "Build and Integrate",
        items: [{ text: "Existing Projects", link: "/guide/existing-projects" }]
      },
      {
        text: "Reference",
        items: [
          { text: "Architecture", link: "/reference/architecture" },
          { text: "Performance", link: "/reference/performance" },
          { text: "API Overview", link: "/api/" }
        ]
      },
      {
        text: "Experimental",
        items: [{ text: "Host Integration", link: "/experimental/host-integration" }]
      }
    ],
    socialLinks: [{ icon: "github", link: "https://github.com/clock/tauri-cpp" }]
  }
});
