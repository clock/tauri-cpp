import { defineConfig } from "vitepress";

export default defineConfig({
  title: "tauri-cpp",
  description: "windows first tauri + c++ starter",
  cleanUrls: true,
  themeConfig: {
    nav: [
      { text: "Guide", link: "/guide/quickstart" },
      { text: "API", link: "/api/" },
      { text: "Examples", link: "/guide/examples" }
    ],
    sidebar: [
      {
        text: "Guide",
        items: [
          { text: "Quickstart", link: "/guide/quickstart" },
          { text: "Examples", link: "/guide/examples" },
          { text: "Existing Projects", link: "/guide/existing-projects" },
          { text: "Performance", link: "/guide/performance" },
          { text: "Host Integration", link: "/guide/host-integration" }
        ]
      },
      {
        text: "Reference",
        items: [{ text: "API Overview", link: "/api/" }]
      }
    ],
    socialLinks: [{ icon: "github", link: "https://github.com/clock/tauri-cpp" }]
  }
});
