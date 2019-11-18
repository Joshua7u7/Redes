"use strict";
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
var __importStar = (this && this.__importStar) || function (mod) {
    if (mod && mod.__esModule) return mod;
    var result = {};
    if (mod != null) for (var k in mod) if (Object.hasOwnProperty.call(mod, k)) result[k] = mod[k];
    result["default"] = mod;
    return result;
};
Object.defineProperty(exports, "__esModule", { value: true });
const express_1 = __importDefault(require("express"));
const multer_1 = __importDefault(require("multer"));
const morgan_1 = __importDefault(require("morgan"));
const cors_1 = __importDefault(require("cors"));
const dotenv = __importStar(require("dotenv"));
const HomeRoutes_1 = __importDefault(require("./routes/HomeRoutes"));
const DocumentRoutes_1 = __importDefault(require("./routes/DocumentRoutes"));
dotenv.config();
class App {
    constructor() {
        this.app = express_1.default();
        this.configureApp();
        this.routes();
    }
    configureApp() {
        this.app.set("port", process.env.PORT || 3000);
        this.app.use(morgan_1.default("dev"));
        this.app.use(cors_1.default({ origin: true }));
        this.app.use(express_1.default.json());
        this.app.use(multer_1.default({
            storage: multer_1.default.diskStorage({
                destination: process.env.FILES_PATH,
                filename: (req, file, cb) => {
                    cb(undefined, file.originalname);
                }
            }),
            dest: process.env.FILES_PATH,
            fileFilter: (req, file, cb) => {
                return cb(undefined, true);
            }
        }).array("net_files"));
    }
    routes() {
        this.app.use(HomeRoutes_1.default);
        this.app.use("/documents", DocumentRoutes_1.default);
    }
    start() {
        this.app.listen(this.app.get("port"), () => {
            console.log("  App is running at http://localhost:%d in %s mode" + "\n", this.app.get("port"), this.app.get("env"));
            console.log("  Press CTRL-C to stop\n ");
        });
    }
}
const app = new App();
exports.default = app;
