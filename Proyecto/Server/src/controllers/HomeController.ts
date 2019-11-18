import { Request, Response } from "express";


class HomeController {

  public index (req: Request, res: Response) {
      res.json({msg: "hello world"});
  }
 
}

const homeController = new HomeController();
export default homeController;