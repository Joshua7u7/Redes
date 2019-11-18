import express, { Application } from "express";
import  multer from "multer";
import  morgan from "morgan";
import cors from "cors";
import * as path from "path";
import * as dotenv from "dotenv";
import HomeRoutes from "./routes/HomeRoutes";
import DocumentsRoutes from "./routes/DocumentRoutes";

dotenv.config();

class App {
    private app: any;
    
    constructor() {
        this.app = express();
        this.configureApp();
        this.routes();
    }

    public configureApp() {
        this.app.set("port", process.env.PORT || 3000);
        this.app.use(morgan("dev"));
        this.app.use(cors({origin: true}));
        this.app.use(express.json());
        this.app.use(multer({
            storage: multer.diskStorage({
              destination: process.env.FILES_PATH ,
              filename: (req: any, file: any, cb: any) => {
                cb( undefined , file.originalname);
              }}),
            dest:  process.env.FILES_PATH,
            fileFilter: (req: any, file: any, cb: any) => {
              return cb( undefined , true);
            }
          }).array("net_files"));
    }

    private routes() {
      this.app.use(HomeRoutes);
      this.app.use("/documents", DocumentsRoutes);
    }

    public start(): void {
      this.app.listen(this.app.get("port"), () => {
        console.log(
          "  App is running at http://localhost:%d in %s mode" + "\n" ,
          this.app.get("port"),
          this.app.get("env"),
        );
        console.log("  Press CTRL-C to stop\n ");
      });
    }

}

const app: App = new App();
export default app;