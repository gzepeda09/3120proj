import pandas as pd
import io
import numpy as np

import seaborn as sns
from matplotlib import pyplot as plt
sns.set(color_codes=True)

%matplotlib inline 
from google.colab import files
 
 
uploaded = files.upload()


 
df = pd.read_csv(io.BytesIO(uploaded['infect.csv']))
df.head(10)

sns.heatmap(df)